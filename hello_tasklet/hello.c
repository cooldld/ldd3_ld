#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h> /*for tasklet api*/
#include <linux/delay.h> /*for msleep*/

static struct tasklet_struct hello_tasklet;
/*DECLARE_TASKLET(hello_tasklet, hello_tasklet_func, 0);*/

static void hello_tasklet_func(unsigned long data)
{
	//msleep(data); /*msleep in tasklet make crash*/
	printk(KERN_ALERT "%s, data=%ld\n", __FUNCTION__, data);
}

static int __init hello_init(void)
{
	int data = 1000;

	printk(KERN_ALERT "Hello, world\n");
	tasklet_init(&hello_tasklet, hello_tasklet_func, data);
	tasklet_schedule(&hello_tasklet);

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
	tasklet_kill(&hello_tasklet);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
