#include <linux/init.h>
#include <linux/module.h>

void hello2_test(void)
{
	printk(KERN_ALERT "hello2 test\n");
}
