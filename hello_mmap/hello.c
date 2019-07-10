#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>  /*for kzalloc()*/
#include <linux/uaccess.h>  /*for copy_from/to_user()*/
#include <linux/mm.h>  /*for remap_pfn_range*/

#define HELLO_DATA_LEN 1024

static int hello_major = 0;
static struct cdev hello_cdev;
static char *hello_data;
static unsigned long phys_addr;

static int hello_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static int hello_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "%s\n", __FUNCTION__);
	return 0;
}

static int hello_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long pfn;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	pfn = phys_addr >> PAGE_SHIFT;
	vma->vm_flags |= VM_IO;
	vma->vm_flags |= VM_NORESERVE;

	if (remap_pfn_range(vma, vma->vm_start, pfn, vma->vm_end - vma->vm_start,
			vma->vm_page_prot))
	{
		printk(KERN_ALERT "remap_pfn_range fail\n");
		return -EAGAIN;
	}

	return 0;
}

static struct file_operations hello_fops = {
	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.mmap = hello_mmap,
};

static void hello_setup_cdev(int index)
{
	int err;
	dev_t devno;

	/*init*/
	devno = MKDEV(hello_major, index);

	cdev_init(&hello_cdev, &hello_fops);
	hello_cdev.owner = THIS_MODULE;
	err = cdev_add(&hello_cdev, devno, 1);
	if (err)
	{
		printk(KERN_NOTICE "cdev_add fail, index=%d, err=%d\n", index, err);
	}
}

static int __init hello_init(void)
{
#define CHRDEV_NAME "hello"
	int ret;
	dev_t devno;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	/*init*/
	ret = -1;
	devno = MKDEV(hello_major, 0);

	if (hello_major)
	{
		ret = register_chrdev_region(devno, 1, CHRDEV_NAME);
	}
	else
	{
		ret = alloc_chrdev_region(&devno, 0, 1, CHRDEV_NAME);
		hello_major = MAJOR(devno);
	}
	if (ret < 0)
	{
		printk(KERN_NOTICE "register chrdev fail\n");
		return ret;
	}

	printk(KERN_ALERT "major=%d, minor=%d\n", MAJOR(devno), MINOR(devno));

	hello_setup_cdev(0);

	hello_data = kmalloc(HELLO_DATA_LEN, GFP_KERNEL);
	if (NULL == hello_data)
	{
		printk(KERN_ALERT "kmalloc fail\n");
		return -1;
	}
	printk(KERN_ALERT "hello_data=0x%p\n", hello_data);

	memset(hello_data, 0, HELLO_DATA_LEN);
	phys_addr = virt_to_phys(hello_data);
	printk(KERN_ALERT "phys_addr=0x%lx\n", phys_addr);

	snprintf(hello_data, HELLO_DATA_LEN, "%s", "hello world");

	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	kfree(hello_data);
	cdev_del(&hello_cdev);
	unregister_chrdev_region(MKDEV(hello_major, 0), 1);

	printk(KERN_ALERT "%s\n", __FUNCTION__);
}
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");
