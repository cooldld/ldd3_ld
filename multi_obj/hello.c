#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

extern void hello2_test(void);

static int __init hello_init(void)
{
	printk(KERN_ALERT "hello, test\n");
	hello2_test();

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "hello, goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
