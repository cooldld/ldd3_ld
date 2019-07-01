#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

static void count_timer_handler(struct timer_list *timer);

#if 0
static struct timer_list count_timer;
#else
static DEFINE_TIMER(count_timer, count_timer_handler);
#endif
static int count = 0;

static void count_timer_handler(struct timer_list *timer)
{
	mod_timer(timer, jiffies + HZ);
	printk(KERN_ALERT "count=%d\n", count);
	count++;
}

static int __init timer_test_init(void)
{
	/*timer_setup(&count_timer, count_timer_handler, 0);*/
	add_timer(&count_timer);
	return 0;
}

static void __exit timer_test_exit(void)
{
    del_timer(&count_timer);
	printk(KERN_ALERT "%s\n", __FUNCTION__);
}

module_init(timer_test_init);
module_exit(timer_test_exit);

MODULE_LICENSE("Dual BSD/GPL");
