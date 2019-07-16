#include <linux/module.h>
#include <linux/platform_device.h>

static struct platform_device *hello_device;

static int __init hello_device_init(void)
{
	int ret;

	printk(KERN_ALERT "hello platform device init\n");

	hello_device = platform_device_alloc("hello_platform", -1);
	if (NULL == hello_device)
	{
		printk(KERN_ALERT "platform_device_alloc fail\n");
		return -ENOMEM;
	}

	ret = platform_device_add(hello_device);
	if (ret)
	{
		printk(KERN_ALERT "platform_device_add fail\n");
		return ret;
	}

	return 0;
}
module_init(hello_device_init);

static void __exit hello_device_exit(void)
{
	printk(KERN_ALERT "hello platform device exit\n");
	platform_device_unregister(hello_device);
}
module_exit(hello_device_exit);

MODULE_LICENSE("Dual BSD/GPL");
