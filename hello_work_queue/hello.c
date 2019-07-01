#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h> /*for tasklet api*/
#include <linux/delay.h> /*for msleep*/

static struct work_struct hello_wq;

static void hello_wq_func(struct work_struct *work)
{
	int sleep = 7000;
	printk(KERN_ALERT "%s, work=0x%p, sleep=%dms\n", __FUNCTION__, work, sleep);
	msleep(sleep); /*work queue can sleep*/
	printk(KERN_ALERT "%s, sleep finish\n", __FUNCTION__);
}

static int __init hello_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	INIT_WORK(&hello_wq, hello_wq_func);
	schedule_work(&hello_wq);

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
