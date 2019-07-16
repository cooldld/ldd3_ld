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

static int hello_driver_probe(struct platform_device *pdev)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static int hello_driver_remove(struct platform_device *pdev)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
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
