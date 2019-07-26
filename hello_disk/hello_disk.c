#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>  /*for kzalloc()*/
#include <linux/uaccess.h>  /*for copy_from/to_user()*/
#include <linux/mm.h>  /*for remap_pfn_range*/
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_device.h>
#include <linux/hdreg.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/bio.h>

static int use_request_queue = 1; /*1:use request queue, 0:no request queue*/
static int is_print_data = 0; /*debug*/

module_param(use_request_queue, int, S_IRUGO);
module_param(is_print_data, int, S_IRUGO);

#define SECTOR_SIZE 512
#define SECTOR_NUM 1024
#define DISK_NUM 1

#define DISK_MINORS 16
#define KERNEL_SECTOR_SIZE 512

struct hello_disk_dev
{
	int size;
	u8 *data;
	spinlock_t lock;
	struct request_queue *queue;
	struct gendisk *gd;
};

static struct hello_disk_dev *hello_disk_devices;
static int hello_major;

typedef unsigned char uint8;
typedef signed int int32;

static void print_data(char *msg, uint8 *data, int32 len)
{
#define LINE_NUMBER 32
    int32 i;
    char str[LINE_NUMBER*4];/* 0x00 = "00 ", 1个字节要用4个字符来存储*/
    int32 pos, ret;

    if (NULL == msg)
    {
        msg = "data";
    }

    printk(KERN_ALERT "%s, len=%d, binary:", msg, len);

    pos = 0;
    for (i = 0; i < len; i++)
    {
        if ((i != 0) && (i % LINE_NUMBER == 0))
        {
            printk(KERN_ALERT "%s", str);
            pos = 0;
        }
        else if ((i != 0) && (i % 4 == 0))
        {
            ret = sprintf(str + pos, "%s", " ");
            pos += ret;
        }
        ret = sprintf(str + pos, "%02x ", data[i]);
        pos += ret;
    }

    if (pos > 0)
    {
        printk(KERN_ALERT "%s", str);
    }
}

/*handle an i/o request*/
static void hello_disk_transfer(struct hello_disk_dev *dev, unsigned long sector,
		unsigned long nsect, char *buffer, int is_write)
{
	unsigned long offset = sector * KERNEL_SECTOR_SIZE;
	unsigned long nbytes = nsect * KERNEL_SECTOR_SIZE;

	printk(KERN_ALERT "%s, offset=%lu, nbytes=%lu\n", __FUNCTION__, offset, nbytes);

	if ((offset + nbytes) > dev->size)
	{
		printk(KERN_ALERT "error, offset=%ld, nbytes=%ld, size=%d\n",
				offset, nbytes, dev->size);
		return;
	}

	if (is_write)
	{
		if (is_print_data)
		{
			print_data("write", buffer, nbytes);
		}
		memmove(dev->data + offset, buffer, nbytes);
	}
	else
	{
		if (is_print_data)
		{
			print_data("read", dev->data + offset, nbytes);
		}
		memmove(buffer, dev->data + offset, nbytes);
	}
}

/*
* queues that have highmem support enabled may still need to revert to
* PIO transfers occasionally and thus map high pages temporarily. For
* permanent PIO fall back, user is probably better off disabling highmem
* I/O completely on that queue (see ide-dma for example)
 */
#define __bio_kmap_atomic(bio, iter) \
		(kmap_atomic(bio_iter_iovec((bio), (iter)).bv_page) + \
				bio_iter_iovec((bio), (iter)).bv_offset)

#define __bio_kunmap_atomic(addr)	kunmap_atomic(addr)

/*transfer a single bio*/
static int hello_disk_xfer_bio(struct hello_disk_dev *dev, struct bio *bio)
{
	struct bio_vec bvec;
	struct bvec_iter iter;
	sector_t sector;
	unsigned long nsect;
	char *buffer;
	int is_write;

	printk(KERN_ALERT "%s start\n", __FUNCTION__);

	bio_for_each_segment(bvec, bio, iter)
	{
		printk(KERN_ALERT "bio_for_each_segment, iter=0x%p\n", &iter);

		sector = bio->bi_iter.bi_sector;
		nsect = bio_cur_bytes(bio) >> 9;
		buffer = __bio_kmap_atomic(bio, iter);
		is_write = (bio_data_dir(bio) == WRITE);

		printk(KERN_ALERT "sector=%lu, nsect=%lu, buffer=0x%p, is_write=%d\n",
				sector, nsect, buffer, is_write);

		hello_disk_transfer(dev, sector, nsect, buffer, is_write);
		sector += nsect;

		__bio_kunmap_atomic(buffer);
	}

	printk(KERN_ALERT "%s end\n", __FUNCTION__);
	return 0;
}

/*disk with request queue*/
static void hello_disk_request(struct request_queue *q)
{
	struct request *req;
	struct bio *bio;
	struct hello_disk_dev *dev;

	printk(KERN_ALERT "%s start, request_queue=0x%p\n", __FUNCTION__, q);

	while ((req = blk_peek_request(q)) != NULL)
	{
		printk(KERN_ALERT "blk_peek_request, req=0x%p\n", req);

#if 0
		if (req->cmd_type != REQ_TYPE_FS)
		{
			printk(KERN_ALERT "not support, cmd_type=%d\n", req->cmd_type);
			blk_start_request(req);
			__blk_end_request_all(req, -EIO);
			continue;
		}
#endif

		dev = req->rq_disk->private_data;
		/*printk(KERN_ALERT "req->rq_disk->private_data=0x%p\n", dev);*/

		blk_start_request(req);
		__rq_for_each_bio(bio, req)
		{
			printk(KERN_ALERT "__rq_for_each_bio, bio=0x%p\n", bio);
			hello_disk_xfer_bio(dev, bio);
		}
		__blk_end_request_all(req, 0);
	}

	printk(KERN_ALERT "%s end\n", __FUNCTION__);
}

/*disk without request queue*/
static blk_qc_t hello_disk_make_request(struct request_queue *q, struct bio *bio)
{
	struct hello_disk_dev *dev = q->queuedata;
	int status;

	printk(KERN_ALERT "%s, request_queue=0x%p, bio=0x%p\n", __FUNCTION__, q, bio);

	status = hello_disk_xfer_bio(dev, bio);
#if 0
	bio_endio(bio, status);
#else
	bio_endio(bio);
#endif

	return (blk_qc_t)status;
}

static int hello_disk_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	long size;
	struct hello_disk_dev *dev = bdev->bd_disk->private_data;

	printk(KERN_ALERT "%s, bdev->bd_disk->private_data=0x%p, size=%d\n",
			__FUNCTION__, dev, dev->size);

	size = dev->size * (SECTOR_SIZE / KERNEL_SECTOR_SIZE);
	geo->cylinders = (size & ~0x3f) >> 6;
	geo->heads = 4;
	geo->sectors = 16;
	geo->start = 4;

	return 0;
}

/*hello disk operations*/
static struct block_device_operations hello_disk_ops =
{
	.getgeo = hello_disk_getgeo,
};

static void hello_setup_device(struct hello_disk_dev *dev, int which)
{
	printk(KERN_ALERT "%s, which=%d, dev=0x%p\n", __FUNCTION__, which, dev);

	memset(dev, 0, sizeof(*dev));
	dev->size = SECTOR_NUM * SECTOR_SIZE;
	dev->data = vmalloc(dev->size);
	if (NULL == dev->data)
	{
		printk(KERN_ALERT "vmalloc error, size=%d\n", dev->size);
		return;
	}
	spin_lock_init(&dev->lock);

	if (use_request_queue)
	{
		dev->queue = blk_init_queue(hello_disk_request, &dev->lock);
		if (NULL == dev->queue)
		{
			printk(KERN_ALERT "blk_init_queue error\n");
			goto fail;
		}
		printk(KERN_ALERT "blk_init_queue=0x%p\n", dev->queue);
	}
	else
	{
		dev->queue = blk_alloc_queue(GFP_KERNEL);
		if (NULL == dev->queue)
		{
			printk(KERN_ALERT "blk_init_queue error\n");
			goto fail;
		}
		printk(KERN_ALERT "blk_alloc_queue=0x%p\n", dev->queue);

		blk_queue_make_request(dev->queue, hello_disk_make_request);
	}

	blk_queue_logical_block_size(dev->queue, SECTOR_SIZE);
	dev->queue->queuedata = dev;

	dev->gd = alloc_disk(DISK_MINORS);
	if (NULL == dev->gd)
	{
		printk(KERN_ALERT "alloc_disk error\n");
		goto fail;
	}
	printk(KERN_ALERT "alloc_disk, dev->gd=0x%p\n", dev->gd);

	dev->gd->major = hello_major;
	dev->gd->first_minor = which * DISK_MINORS;
	dev->gd->fops = &hello_disk_ops;
	dev->gd->queue = dev->queue;
	dev->gd->private_data = dev;
	snprintf(dev->gd->disk_name, 32, "hello_disk%c", which + 'a');
	set_capacity(dev->gd, SECTOR_NUM * (SECTOR_SIZE / KERNEL_SECTOR_SIZE));
	printk(KERN_ALERT "add_disk start, which=%d\n", which);
	add_disk(dev->gd);
	printk(KERN_ALERT "add_disk end, which=%d\n", which);

	return;

fail:
	if (dev->data)
	{
		vfree(dev->data);
	}
}

static int __init hello_disk_init(void)
{
	int i;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	hello_major = register_blkdev(0, "hello_disk");
	if (hello_major < 0)
	{
		printk(KERN_ALERT "register_blkdev fail, hello_major=%d\n", hello_major);
		return -EBUSY;
	}
	printk(KERN_ALERT "register_blkdev, hello_major=%d\n", hello_major);

	hello_disk_devices = kmalloc(DISK_NUM * sizeof(struct hello_disk_dev), GFP_KERNEL);
	if (NULL == hello_disk_devices)
	{
		printk(KERN_ALERT "kmalloc fail\n");
		goto fail;
	}

	printk(KERN_ALERT "hello_disk_devices=0x%p\n", hello_disk_devices);

	for (i = 0; i < DISK_NUM; i++)
	{
		hello_setup_device(hello_disk_devices + i, i);
	}

	return 0;

fail:
	unregister_blkdev(hello_major, "hello_disk");
	return -ENOMEM;
}
module_init(hello_disk_init);

static void hello_disk_exit(void)
{
	int i;
	struct hello_disk_dev *dev;

	printk(KERN_ALERT "%s\n", __FUNCTION__);

	for (i = 0; i < DISK_NUM; i++)
	{
		dev = hello_disk_devices + i;

		if (dev->gd)
		{
			del_gendisk(dev->gd);
			put_disk(dev->gd);
			printk(KERN_ALERT "i=%d, del_gendisk and put_disk\n", i);
		}
		if (dev->queue)
		{
			if (use_request_queue)
			{
				blk_cleanup_queue(dev->queue);
				printk(KERN_ALERT "i=%d, blk_cleanup_queue\n", i);
			}
			else
			{
				kobject_put(&dev->queue->kobj);
				printk(KERN_ALERT "i=%d, kobject_put\n", i);
			}
		}
	}

	unregister_blkdev(hello_major, "hello_disk");
	kfree(hello_disk_devices);
	printk(KERN_ALERT "unregister_blkdev and kfree\n");
}
module_exit(hello_disk_exit);

MODULE_LICENSE("Dual BSD/GPL");
