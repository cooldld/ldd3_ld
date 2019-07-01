#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h> /*for kzalloc()*/
#include <linux/uaccess.h> /*for copy_from/to_user()*/
#include <linux/sched/signal.h> /*for signal_pending()*/
#include <linux/poll.h> /*for poll_table*/

#define GMEM_SIZE 10 //0x1000

static int gmem_major = 0;

module_param(gmem_major, int, S_IRUGO);

struct gmem_dev
{
	struct cdev cdev;
	int len;
	unsigned char data[GMEM_SIZE];
	struct mutex mutex;
	wait_queue_head_t r_wait;
	wait_queue_head_t w_wait;
};

struct gmem_dev *gmem_device;

static int gmem_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	filp->private_data = gmem_device;
	return 0;
}

static int gmem_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static ssize_t gmem_read(struct file *filp, char __user *buf, size_t count,
		loff_t *f_pos)
{
	struct gmem_dev *dev;
	ssize_t ret;
	DECLARE_WAITQUEUE(wait, current);

	/*init*/
	dev = filp->private_data;
	ret = 0;

	printk(KERN_ALERT "%s, current len=%d\n", __FUNCTION__, dev->len);

	mutex_lock(&dev->mutex);
	add_wait_queue(&dev->r_wait, &wait);

	while (0 == dev->len)
	{
		if (filp->f_flags & O_NONBLOCK)
		{
			ret = -EAGAIN;
			goto out;
		}
		__set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&dev->mutex);

		schedule();
		if (signal_pending(current))
		{
			printk(KERN_ALERT "%s, wake by singal\n", __FUNCTION__);
			ret = -ERESTARTSYS;
			goto out2;
		}

		mutex_lock(&dev->mutex);
	}

	if (count > dev->len)
	{
		count = dev->len;
	}

	if (copy_to_user(buf, dev->data, count))
	{
		ret = -EFAULT;
		goto out;
	}
	else
	{
		memmove(dev->data, dev->data + count, dev->len - count);
		dev->len -= count;
		ret = count;

		printk(KERN_ALERT "read count=%ld, len=%d\n", count, dev->len);

		wake_up_interruptible(&dev->w_wait);
	}

out:
	mutex_unlock(&dev->mutex);
out2:
	remove_wait_queue(&dev->r_wait, &wait);
	set_current_state(TASK_RUNNING);

	return ret;
}

static ssize_t gmem_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	struct gmem_dev *dev;
	ssize_t ret;
	DECLARE_WAITQUEUE(wait, current);

	/*init*/
	dev = filp->private_data;
	ret = 0;

	printk(KERN_ALERT "%s, current len=%d\n", __FUNCTION__, dev->len);

	mutex_lock(&dev->mutex);
	add_wait_queue(&dev->w_wait, &wait);

	while (dev->len == GMEM_SIZE)
	{
		if (filp->f_flags & O_NONBLOCK)
		{
			ret = -EAGAIN;
			goto out;
		}

		__set_current_state(TASK_INTERRUPTIBLE);

		mutex_unlock(&dev->mutex);

		schedule();
		if (signal_pending(current))
		{
			printk(KERN_ALERT "%s, wake by singal\n", __FUNCTION__);
			ret = -ERESTARTSYS;
			goto out2;
		}

		mutex_lock(&dev->mutex);
	}

	if (count + dev->len > GMEM_SIZE)
	{
		count = GMEM_SIZE - dev->len;
	}

	if (copy_from_user(dev->data + dev->len, buf, count))
	{
		ret = -EFAULT;
		goto out;
	}
	else
	{
		dev->len += count;
		ret = count;

		printk(KERN_ALERT "write, count=%ld\n", count);

		wake_up_interruptible(&dev->r_wait);
	}

out:
	mutex_unlock(&dev->mutex);
out2:
	remove_wait_queue(&dev->w_wait, &wait);
	set_current_state(TASK_RUNNING);

	return ret;
}

static loff_t gmem_llseek(struct file *filp, loff_t offset, int whence)
{
	loff_t ret = 0;

	printk(KERN_ALERT "%s, offset=%lld, whence=%d\n",
			__FUNCTION__, offset, whence);

	switch (whence)
	{
	case 0:
		if (offset < 0)
		{
			ret = -EINVAL;
			break;
		}
		if ((unsigned int)offset > GMEM_SIZE)
		{
			ret = -EINVAL;
			break;
		}
		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;
	case 1:
		if ((filp->f_pos + offset) > GMEM_SIZE)
		{
			ret = -EINVAL;
			break;
		}
		if ((filp->f_pos + offset) < 0)
		{
			ret = -EINVAL;
			break;
		}
		filp->f_pos += offset;
		ret = filp->f_pos;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

#define GMEM_IOCTL_TYPE 100
#define GMEM_CLEAR_NR 0

#define GMEM_IOCTL_CLEAR _IO(GMEM_IOCTL_TYPE, GMEM_CLEAR_NR)

static long gmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct gmem_dev *dev = filp->private_data;

	printk(KERN_ALERT "%s, cmd=%d, arg=%ld\n",
			__FUNCTION__, cmd, arg);

	switch (cmd)
	{
	case GMEM_IOCTL_CLEAR:
		mutex_lock(&dev->mutex);
		memset(dev->data, 0, GMEM_SIZE);
		mutex_unlock(&dev->mutex);
		printk(KERN_ALERT "gmem clear\n");
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static unsigned int gmem_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask = 0;
	struct gmem_dev *dev = filp->private_data;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	mutex_lock(&dev->mutex);

	poll_wait(filp, &dev->r_wait, wait);
	poll_wait(filp, &dev->w_wait, wait);

	/*can read*/
	if (dev->len > 0)
	{
		mask |= POLLIN | POLLRDNORM;
	}

	/*can write*/
	if (dev->len < GMEM_SIZE)
	{
		mask |= POLLOUT | POLLWRNORM;
	}

	mutex_unlock(&dev->mutex);

	return mask;
}

static struct file_operations gmem_fops = {
	.owner = THIS_MODULE,
	.open = gmem_open,
	.release = gmem_release,
	.read = gmem_read,
	.write = gmem_write,
	.llseek = gmem_llseek,
	.unlocked_ioctl = gmem_ioctl,
	.poll = gmem_poll,
};

static void gmem_setup_cdev(struct gmem_dev *dev, int index)
{
	int err;
	dev_t devno;

	/*init*/
	devno = MKDEV(gmem_major, index);

	cdev_init(&dev->cdev, &gmem_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
	{
		printk(KERN_NOTICE "cdev_add fail, index=%d, err=%d\n", index, err);
	}
}

static int __init gmem_init(void)
{
#define CHRDEV_NAME "gmem"
	int ret;
	dev_t devno;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	/*init*/
	ret = -1;
	devno = MKDEV(gmem_major, 0);

	if (gmem_major)
	{
		ret = register_chrdev_region(devno, 1, CHRDEV_NAME);
	}
	else
	{
		ret = alloc_chrdev_region(&devno, 0, 1, CHRDEV_NAME);
		gmem_major = MAJOR(devno);
	}
	if (ret < 0)
	{
		printk(KERN_NOTICE "register chrdev fail\n");
		return ret;
	}

	printk(KERN_ALERT "major=%d, minor=%d\n", MAJOR(devno), MINOR(devno));

	gmem_device = kzalloc(sizeof(struct gmem_dev), GFP_KERNEL);
	if (NULL == gmem_device)
	{
		printk(KERN_NOTICE "kzalloc fail\n");
		goto fail;
	}

	gmem_setup_cdev(gmem_device, 0);

	mutex_init(&gmem_device->mutex);
	init_waitqueue_head(&gmem_device->r_wait);
	init_waitqueue_head(&gmem_device->w_wait);

	return 0;

fail:
	unregister_chrdev_region(devno, 1);
	return ret;
}
module_init(gmem_init);

static void __exit gmem_exit(void)
{
	cdev_del(&gmem_device->cdev);
	kfree(gmem_device);
	unregister_chrdev_region(MKDEV(gmem_major, 0), 1);

	printk(KERN_ALERT "%s\n", __FUNCTION__);
}
module_exit(gmem_exit);

MODULE_LICENSE("Dual BSD/GPL");
