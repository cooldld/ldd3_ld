#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

extern void hello2_test(void);

static char *name = "world";
static int count = 2;
static int index[8] = {};
static int n_index = sizeof(index) / sizeof(index[0]);

module_param(name, charp, S_IRUGO);
module_param(count, int, S_IRUGO);
module_param_array(index, int, &n_index, S_IRUGO);

static int __init hello_init(void)
{
    int i;

	printk(KERN_ALERT "hello, name=%s, count=%d, n_index=%d\n",
			name, count, n_index);
	
	for (i = 0; i < n_index; i++)
	{
		printk(KERN_ALERT "index[%d]=%d\n", i, index[i]);
	}

	hello2_test();

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "goodbye, name=%s\n", name);
}

module_init(hello_init);
module_exit(hello_exit);
