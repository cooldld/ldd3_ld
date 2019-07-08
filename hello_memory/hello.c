#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

static unsigned char *ptr1;
static unsigned char *ptr2;
static unsigned char *ptr3;
static unsigned char *ptr4;
static unsigned char *ptr5;
static unsigned char *ptr6;
static unsigned char *ptr7;
static unsigned char *ptr8;
static unsigned char *ptr9;

static int __init hello_init(void)
{
	unsigned char *phys_addr;
	int size;
	int order;

	/*init*/
	size = 100 * 1024;
	order = get_order(size);

	/*GFP_KERNEL*/
	ptr1 = kmalloc(size, GFP_KERNEL);
	*ptr1 = 1;
	phys_addr = (void *)virt_to_phys(ptr1);
	printk(KERN_ALERT "kmalloc GFP_KERNEL, ptr=0x%p, phys_addr=0x%p\n", ptr1, phys_addr);

	/*GFP_USER*/
	ptr2 = kmalloc(size, GFP_USER);
	*ptr2 = 1;
	phys_addr = (void *)virt_to_phys(ptr2);
	printk(KERN_ALERT "kmalloc GFP_USER, ptr=0x%p, phys_addr=0x%p\n", ptr2, phys_addr);

	/*GFP_HIGHUSER*/
	ptr3 = kmalloc(size, GFP_HIGHUSER);
	*ptr3 = 1;
	phys_addr = (void *)virt_to_phys(ptr3);
	printk(KERN_ALERT "kmalloc GFP_HIGHUSER, ptr=0x%p, phys_addr=0x%p\n", ptr3, phys_addr);

	/*GFP_DMA*/
	ptr4 = kmalloc(size, GFP_DMA);
	*ptr4 = 1;
	phys_addr = (void *)virt_to_phys(ptr4);
	printk(KERN_ALERT "kmalloc GFP_DMA, ptr=0x%p, phys_addr=0x%p\n", ptr4, phys_addr);

	/*GFP_KERNEL*/
	ptr5 = (void *)__get_free_pages(GFP_KERNEL, order);
	*ptr5 = 1;
	phys_addr = (void *)virt_to_phys(ptr5);
	printk(KERN_ALERT "__get_free_pages GFP_KERNEL, ptr=0x%p, phys_addr=0x%p\n", ptr5, phys_addr);

	/*GFP_USER*/
	ptr6 = (void *)__get_free_pages(GFP_USER, order);
	*ptr6 = 1;
	phys_addr = (void *)virt_to_phys(ptr6);
	printk(KERN_ALERT "__get_free_pages GFP_USER, ptr=0x%p, phys_addr=0x%p\n", ptr6, phys_addr);

	/*GFP_HIGHUSER*/
	ptr7 = (void *)__get_free_pages(GFP_HIGHUSER, order);
	*ptr7 = 1;
	phys_addr = (void *)virt_to_phys(ptr7);
	printk(KERN_ALERT "__get_free_pages GFP_HIGHUSER, ptr=0x%p, phys_addr=0x%p\n", ptr7, phys_addr);

	/*GFP_DMA*/
	ptr8 = (void *)__get_free_pages(GFP_DMA, order);
	*ptr8 = 1;
	phys_addr = (void *)virt_to_phys(ptr8);
	printk(KERN_ALERT "__get_free_pages GFP_DMA, ptr=0x%p, phys_addr=0x%p\n", ptr8, phys_addr);

	/*vmalloc*/
	ptr9 = vmalloc(size);
	*ptr9 = 1;
	phys_addr = (void *)virt_to_phys(ptr9);
	printk(KERN_ALERT "vmalloc, ptr=0x%p, phys_addr=0x%p\n", ptr9, phys_addr);

	return 0;
}

static void __exit hello_exit(void)
{
	kfree(ptr1);
	kfree(ptr2);
	kfree(ptr3);
	kfree(ptr4);
	free_page((unsigned long)ptr5);
	free_page((unsigned long)ptr6);
	free_page((unsigned long)ptr7);
	free_page((unsigned long)ptr8);
	vfree(ptr9);
	printk(KERN_ALERT "%s\n", __FUNCTION__);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
