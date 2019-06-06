#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h> /*for kzalloc()*/

#define GMEM_SIZE 0x1000
#define GMEM_MAJOR 230

static int gmem_major = 0;

module_param(gmem_major, int, S_IRUGO);

struct gmem_dev {
	struct cdev cdev;
	unsigned char data[GMEM_SIZE];
};

struct gmem_dev *gmem_device;

static void gmem_setup_cdev(struct gmem_dev *dev, int index)
{
	int err;
	dev_t devno;

	/*init*/
	devno = MKDEV(gmem_major, index);

	cdev_init(&dev->cdev, NULL); /**FIXME NULL should be gmem_fops*/
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
	{
		printk(KERN_NOTICE "cdev_add fail, index=%d, err=%d", index, err);
	}
}

static int __init gmem_init(void)
{
	int ret;
	dev_t devno;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	/*init*/
	ret = -1;
	devno = MKDEV(gmem_major, 0);

	if (gmem_major)
	{
		ret = register_chrdev_region(devno, 1, "gmem");
	}
	else
	{
		ret = alloc_chrdev_region(&devno, 0, 1, "gmen");
		gmem_major = MAJOR(devno);
	}
	if (ret < 0)
	{
		printk(KERN_NOTICE "register chrdev fail");
		return ret;
	}

	gmem_device = kzalloc(sizeof(struct gmem_dev), GFP_KERNEL);
	if (NULL == gmem_device)
	{
		printk(KERN_NOTICE "kzalloc fail");
		goto fail;
	}

	gmem_setup_cdev(gmem_device, 0);
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
