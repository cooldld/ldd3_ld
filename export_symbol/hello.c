#include <linux/init.h>
#include <linux/module.h>

extern int add_integar(int a, int b);
extern int sub_integar(int a, int b);

static int __init hello_init(void)
{
	printk(KERN_ALERT "call add_integar(2, 3)=%d\n", add_integar(2, 3));
	printk(KERN_ALERT "call sub_integar(2, 3)=%d\n", sub_integar(2, 3));
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "%s exit\n", __FUNCTION__);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
