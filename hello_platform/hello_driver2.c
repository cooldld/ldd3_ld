#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>  /*for kzalloc()*/
#include <linux/uaccess.h>  /*for copy_from/to_user()*/
#include <linux/mm.h>  /*for remap_pfn_range*/
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_device.h>

static struct miscdevice hello_miscdevice;

static int hello_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static int hello_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static ssize_t hello_read(struct file *filp, char __user *buf, size_t count,
		loff_t *f_pos)
{
	printk(KERN_ALERT "%s, f_pos=%lld\n", __FUNCTION__, *f_pos);
	return 0;
}

static ssize_t hello_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "%s, f_pos=%lld\n", __FUNCTION__, *f_pos);
	return 0;
}

static const struct file_operations hello_fops =
{
	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
	.write = hello_write,
};

static int hello_driver_probe(struct platform_device *pdev)
{
	int ret;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	hello_miscdevice.minor = MISC_DYNAMIC_MINOR;
	hello_miscdevice.name = "hello_miscdevice";
	hello_miscdevice.fops = &hello_fops;

	platform_set_drvdata(pdev, &hello_miscdevice);

	ret = misc_register(&hello_miscdevice);
	if (ret < 0)
	{
		printk(KERN_ALERT "misc_register fail\n");
		goto fail;
	}

	dev_info(&pdev->dev, "hello_miscdevice register");
	return 0;

fail:
	return ret;
}

static int hello_driver_remove(struct platform_device *pdev)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);

	misc_deregister(&hello_miscdevice);
	dev_info(&pdev->dev, "hello_miscdevice deregister");

	return 0;
}

static struct platform_driver hello_driver =
{
	.driver =
	{
		.name = "hello_platform",
		.owner = THIS_MODULE,
	},
	.probe = hello_driver_probe,
	.remove = hello_driver_remove,
};

module_platform_driver(hello_driver);

MODULE_LICENSE("Dual BSD/GPL");
