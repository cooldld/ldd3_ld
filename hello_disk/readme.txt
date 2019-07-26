block设备的demo程序

问题：
char *ptr = kmalloc(10, GFP_KERNEL);
printk("%p", ptr);
printk("%lx", (unsigned long)ptr);
上面两个语句输出的十六进制数据完全不一样
（经过验证，在应用程序中没有类似问题）

insmod这个模块时有两个入参
use_request_queue=0/1  #1表示使用request queue，0表示使用make request，默认1
is_print_data=0/1  #1表示输出读写数据，0表示不输出，默认0

#支持request queue的block设备
$ sudo insmod hello_disk.ko

dmesg info
hello_disk_init
register_blkdev, hello_major=252
hello_disk_devices=0x000000008fd6d058
hello_setup_device, which=0, dev=0x000000008fd6d058
blk_init_queue=0x00000000337ca401
alloc_disk, dev->gd=0x00000000a655d5d6
add_disk start, which=0
	hello_disk_request start, request_queue=0x00000000337ca401
		blk_peek_request, req=0x00000000ca6f6b9d
		__rq_for_each_bio, bio=0x000000001e7a8bc7
		hello_disk_xfer_bio start
			bio_for_each_segment, iter=0x0000000091f11dc1
			sector=0, nsect=8, buffer=0x0000000010a2262a, is_write=0
			hello_disk_transfer, offset=0, nbytes=4096
		hello_disk_xfer_bio end
	hello_disk_request end

	hello_disk_request start, request_queue=0x00000000337ca401
	hello_disk_request end

	hello_disk_request start, request_queue=0x00000000337ca401
		blk_peek_request, req=0x00000000ca6f6b9d
		__rq_for_each_bio, bio=0x000000001e7a8bc7
		hello_disk_xfer_bio start
			bio_for_each_segment, iter=0x000000005654aece
			sector=8, nsect=8, buffer=0x00000000c83a1edb, is_write=0
			hello_disk_transfer, offset=4096, nbytes=4096
		hello_disk_xfer_bio end
	hello_disk_request end

	hello_disk_request start, request_queue=0x00000000337ca401
	hello_disk_request end

	hello_disk_request start, request_queue=0x00000000337ca401
		blk_peek_request, req=0x00000000ca6f6b9d
		__rq_for_each_bio, bio=0x000000001e7a8bc7
		hello_disk_xfer_bio start
			bio_for_each_segment, iter=0x000000002773d717
			sector=24, nsect=8, buffer=0x000000002e4bbc2f, is_write=0
			hello_disk_transfer, offset=12288, nbytes=4096
		hello_disk_xfer_bio end
	hello_disk_request end

	hello_disk_request start, request_queue=0x00000000337ca401
	hello_disk_request end
add_disk end, which=0

$ sudo mkfs.ext4 /dev/hello_diska
mke2fs 1.44.1 (24-Mar-2018)

Filesystem too small for a journal
Creating filesystem with 512 1k blocks and 64 inodes

Allocating group tables: done
Writing inode tables: done
Writing superblocks and filesystem accounting information: done

dmesg info
hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=8, nsect=8, buffer=0x0000000097162062, is_write=0
		hello_disk_transfer, offset=4096, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=0, nsect=8, buffer=0x00000000baef1f77, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=24, nsect=8, buffer=0x00000000eb9b8184, is_write=0
		hello_disk_transfer, offset=12288, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=56, nsect=8, buffer=0x000000007e9c0e6e, is_write=0
		hello_disk_transfer, offset=28672, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=120, nsect=8, buffer=0x00000000004f8d76, is_write=0
		hello_disk_transfer, offset=61440, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=16, nsect=8, buffer=0x00000000f8590346, is_write=0
		hello_disk_transfer, offset=8192, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=128, nsect=8, buffer=0x0000000011c6ffcf, is_write=0
		hello_disk_transfer, offset=65536, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=64, nsect=8, buffer=0x00000000cfc6aa29, is_write=0
		hello_disk_transfer, offset=32768, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=512, nsect=8, buffer=0x0000000017abb924, is_write=0
		hello_disk_transfer, offset=262144, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=32, nsect=8, buffer=0x00000000c0dca8df, is_write=0
		hello_disk_transfer, offset=16384, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=0, nsect=8, buffer=0x00000000baef1f77, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000537360f6
		sector=24, nsect=8, buffer=0x0000000097162062, is_write=0
		hello_disk_transfer, offset=12288, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000f38c5ad1
		sector=0, nsect=8, buffer=0x00000000baef1f77, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096

		bio_for_each_segment, iter=0x00000000f38c5ad1
		sector=0, nsect=8, buffer=0x0000000097162062, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096

		bio_for_each_segment, iter=0x00000000f38c5ad1
		sector=0, nsect=8, buffer=0x00000000f8590346, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096

		bio_for_each_segment, iter=0x00000000f38c5ad1
		sector=0, nsect=8, buffer=0x00000000eb9b8184, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=0, nsect=8, buffer=0x00000000baef1f77, is_write=0
		hello_disk_transfer, offset=0, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=16, nsect=8, buffer=0x00000000f09787b8, is_write=0
		hello_disk_transfer, offset=8192, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=72, nsect=8, buffer=0x00000000ab613d02, is_write=0
		hello_disk_transfer, offset=36864, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=8, nsect=8, buffer=0x0000000009704a8b, is_write=0
		hello_disk_transfer, offset=4096, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=24, nsect=8, buffer=0x0000000034857129, is_write=0
		hello_disk_transfer, offset=12288, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=32, nsect=8, buffer=0x00000000cd3c0df8, is_write=0
		hello_disk_transfer, offset=16384, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000744425c9
		sector=40, nsect=8, buffer=0x00000000cee1bc32, is_write=0
		hello_disk_transfer, offset=20480, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000ca6f6b9d
	__rq_for_each_bio, bio=0x000000006f3f4553
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=0, nsect=8, buffer=0x00000000baef1f77, is_write=1
		hello_disk_transfer, offset=0, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000a7dad8ba
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=8, nsect=8, buffer=0x0000000009704a8b, is_write=1
		hello_disk_transfer, offset=4096, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000b905f8db
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=16, nsect=8, buffer=0x00000000f09787b8, is_write=1
		hello_disk_transfer, offset=8192, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x0000000064227021
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=24, nsect=8, buffer=0x0000000034857129, is_write=1
		hello_disk_transfer, offset=12288, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x0000000044cd8d3c
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=32, nsect=8, buffer=0x00000000cd3c0df8, is_write=1
		hello_disk_transfer, offset=16384, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000a2f20441
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=40, nsect=8, buffer=0x00000000cee1bc32, is_write=1
		hello_disk_transfer, offset=20480, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000e17700b7
	__rq_for_each_bio, bio=0x00000000473c5733
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=72, nsect=8, buffer=0x00000000ab613d02, is_write=1
		hello_disk_transfer, offset=36864, nbytes=4096
	hello_disk_xfer_bio end

	blk_peek_request, req=0x00000000690820a9
	__rq_for_each_bio, bio=0x0000000009030cf9
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=896, nsect=8, buffer=0x0000000044058e0f, is_write=1
		hello_disk_transfer, offset=458752, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x0000000073caa4e7
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=904, nsect=8, buffer=0x000000004e95b97c, is_write=1
		hello_disk_transfer, offset=462848, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x000000005493cc78
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=912, nsect=8, buffer=0x0000000017abb924, is_write=1
		hello_disk_transfer, offset=466944, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000dee58333
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=920, nsect=8, buffer=0x0000000084b5019c, is_write=1
		hello_disk_transfer, offset=471040, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000325625fe
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=928, nsect=8, buffer=0x000000002875a9a0, is_write=1
		hello_disk_transfer, offset=475136, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000db596de9
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=936, nsect=8, buffer=0x00000000176cd5ce, is_write=1
		hello_disk_transfer, offset=479232, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000d9761c75
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=944, nsect=8, buffer=0x000000008b0419e3, is_write=1
		hello_disk_transfer, offset=483328, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000bfd3d018
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=952, nsect=8, buffer=0x000000000ea12616, is_write=1
		hello_disk_transfer, offset=487424, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x000000000683bfec
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=960, nsect=8, buffer=0x0000000085452eae, is_write=1
		hello_disk_transfer, offset=491520, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x000000006a806fa9
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=968, nsect=8, buffer=0x000000009f8cd7a0, is_write=1
		hello_disk_transfer, offset=495616, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000004904dd
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=976, nsect=8, buffer=0x00000000a070e2cb, is_write=1
		hello_disk_transfer, offset=499712, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000f988a579
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=984, nsect=8, buffer=0x0000000077f2c57e, is_write=1
		hello_disk_transfer, offset=503808, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x000000007056d2d6
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=992, nsect=8, buffer=0x00000000742ec11a, is_write=1
		hello_disk_transfer, offset=507904, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x0000000010a6ba80
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=1000, nsect=8, buffer=0x00000000a492694d, is_write=1
		hello_disk_transfer, offset=512000, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000fa1c99d5
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=1008, nsect=8, buffer=0x00000000dc556417, is_write=1
		hello_disk_transfer, offset=516096, nbytes=4096
	hello_disk_xfer_bio end

	__rq_for_each_bio, bio=0x00000000fc55eb7c
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x0000000022f63c1f
		sector=1016, nsect=8, buffer=0x00000000797b4227, is_write=1
		hello_disk_transfer, offset=520192, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
	blk_peek_request, req=0x00000000690820a9
	__rq_for_each_bio, bio=0x00000000fc55eb7c
	hello_disk_xfer_bio start
		bio_for_each_segment, iter=0x00000000a6756785
		sector=0, nsect=8, buffer=0x00000000baef1f77, is_write=1
		hello_disk_transfer, offset=0, nbytes=4096
	hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end


$ sudo mount /dev/hello_diska xxx

dmesg info
hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
    bio_for_each_segment, iter=0x0000000040acecc6
    sector=8, nsect=8, buffer=0x0000000057c21a24, is_write=0
    hello_disk_transfer, offset=4096, nbytes=4096
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000040acecc6
        sector=0, nsect=8, buffer=0x000000000e54015c, is_write=0
        hello_disk_transfer, offset=0, nbytes=4096
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000040acecc6
        sector=24, nsect=8, buffer=0x00000000f3fc871e, is_write=0
        hello_disk_transfer, offset=12288, nbytes=4096
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000040acecc6
        sector=56, nsect=8, buffer=0x000000005285196e, is_write=0
        hello_disk_transfer, offset=28672, nbytes=4096
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000040acecc6
        sector=120, nsect=8, buffer=0x000000000ccb84b8, is_write=0
        hello_disk_transfer, offset=61440, nbytes=4096
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000a27a8f1a
        sector=2, nsect=2, buffer=0x00000000344c3e67, is_write=0
        hello_disk_transfer, offset=1024, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x000000007f8d0a54
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000059df9314
        sector=4, nsect=2, buffer=0x00000000378da764, is_write=0
        hello_disk_transfer, offset=2048, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x0000000064bfd419
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x000000007ccb65aa
        sector=78, nsect=2, buffer=0x00000000d4c59458, is_write=0
        hello_disk_transfer, offset=39936, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x0000000064bfd419
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000ac87c26a
        sector=76, nsect=2, buffer=0x00000000de31b3d9, is_write=0
        hello_disk_transfer, offset=38912, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x0000000064bfd419
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000fecaa493
        sector=2, nsect=2, buffer=0x00000000344c3e67, is_write=1
        hello_disk_transfer, offset=1024, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x00000000dc5048e8
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x000000009e9a9b28
        sector=14, nsect=2, buffer=0x000000005ba2f13b, is_write=0
        hello_disk_transfer, offset=7168, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x00000000e3141a40
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000744425c9
        sector=80, nsect=8, buffer=0x000000000932f201, is_write=1
        hello_disk_transfer, offset=40960, nbytes=4096

        bio_for_each_segment, iter=0x00000000744425c9
        sector=80, nsect=8, buffer=0x000000000932f201, is_write=1
        hello_disk_transfer, offset=40960, nbytes=4096
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000e17700b7
    __rq_for_each_bio, bio=0x0000000008793f94
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000019ebaacf
        sector=76, nsect=2, buffer=0x00000000de31b3d9, is_write=1
        hello_disk_transfer, offset=38912, nbytes=1024
    hello_disk_xfer_bio end

    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x0000000044cfa227
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000019ebaacf
        sector=4, nsect=2, buffer=0x00000000378da764, is_write=1
        hello_disk_transfer, offset=2048, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end


$ sudo cp hello_64bit.c xxx/

dmesg info
hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x00000000566fafe9
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000015714466
        sector=44, nsect=2, buffer=0x0000000045817461, is_write=0
        hello_disk_transfer, offset=22528, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000a77102b5
    __rq_for_each_bio, bio=0x000000007ae9daf1
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000744425c9
        sector=12, nsect=2, buffer=0x00000000ef4fe812, is_write=0
        hello_disk_transfer, offset=6144, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x0000000024b5623a
    __rq_for_each_bio, bio=0x000000007ae9daf1
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=42, nsect=2, buffer=0x00000000062fadde, is_write=1
        hello_disk_transfer, offset=21504, nbytes=1024
    hello_disk_xfer_bio end

    __rq_for_each_bio, bio=0x0000000010ac61c3
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=44, nsect=2, buffer=0x0000000045817461, is_write=1
        hello_disk_transfer, offset=22528, nbytes=1024
    hello_disk_xfer_bio end

    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x00000000701528c3
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=76, nsect=2, buffer=0x00000000de31b3d9, is_write=1
        hello_disk_transfer, offset=38912, nbytes=1024
    hello_disk_xfer_bio end

    __rq_for_each_bio, bio=0x000000005472fe39
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=78, nsect=2, buffer=0x00000000d4c59458, is_write=1
        hello_disk_transfer, offset=39936, nbytes=1024
    hello_disk_xfer_bio end

    blk_peek_request, req=0x00000000ca6f6b9d
    __rq_for_each_bio, bio=0x00000000566fafe9
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=14, nsect=2, buffer=0x000000005ba2f13b, is_write=1
        hello_disk_transfer, offset=7168, nbytes=1024
    hello_disk_xfer_bio end

    blk_peek_request, req=0x00000000e17700b7
    __rq_for_each_bio, bio=0x0000000069631de0
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=2, nsect=2, buffer=0x00000000344c3e67, is_write=1
        hello_disk_transfer, offset=1024, nbytes=1024
    hello_disk_xfer_bio end

    __rq_for_each_bio, bio=0x00000000b75b1f3b
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x00000000e7166f44
        sector=4, nsect=2, buffer=0x00000000378da764, is_write=1
        hello_disk_transfer, offset=2048, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000ca6f6b9d
    __rq_for_each_bio, bio=0x0000000089f8cdb6
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000077aac65a
        sector=4, nsect=2, buffer=0x00000000378da764, is_write=1
        hello_disk_transfer, offset=2048, nbytes=1024
    hello_disk_xfer_bio end

    blk_peek_request, req=0x00000000690820a9
    __rq_for_each_bio, bio=0x00000000cfac5e91
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000077aac65a
        sector=12, nsect=2, buffer=0x00000000ef4fe812, is_write=1
        hello_disk_transfer, offset=6144, nbytes=1024
    hello_disk_xfer_bio end

    blk_peek_request, req=0x00000000e17700b7
    __rq_for_each_bio, bio=0x00000000b43d4271
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x0000000077aac65a
        sector=78, nsect=2, buffer=0x00000000d4c59458, is_write=1
        hello_disk_transfer, offset=39936, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end


$ cat xxx/hello_64bit.c

dmesg info
hello_disk_request start, request_queue=0x00000000337ca401
    blk_peek_request, req=0x00000000e17700b7
    __rq_for_each_bio, bio=0x00000000fc55eb7c
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x000000002b305def
        sector=76, nsect=2, buffer=0x00000000de31b3d9, is_write=1
        hello_disk_transfer, offset=38912, nbytes=1024
    hello_disk_xfer_bio end

    __rq_for_each_bio, bio=0x00000000aa221827
    hello_disk_xfer_bio start
        bio_for_each_segment, iter=0x000000002b305def
        sector=78, nsect=2, buffer=0x00000000d4c59458, is_write=1
        hello_disk_transfer, offset=39936, nbytes=1024
    hello_disk_xfer_bio end
hello_disk_request end

hello_disk_request start, request_queue=0x00000000337ca401
hello_disk_request end


$ sudo rmmod hello_disk

dmesg info
Jul 25 13:57:52 ub18 kernel: [116330.899253] hello_disk_exit
Jul 25 13:57:52 ub18 kernel: [116330.906324] i=0, del_gendisk and put_disk
Jul 25 13:57:52 ub18 kernel: [116330.910668] i=0, blk_cleanup_queue
Jul 25 13:57:52 ub18 kernel: [116330.910671] unregister_blkdev and kfree


#支持make request的block设备
$ sudo insmod hello_disk.ko use_request_queue=0 is_print_data=1

dmesg info
Jul 25 13:59:45 ub18 kernel: [116444.573144] hello_disk_init
Jul 25 13:59:45 ub18 kernel: [116444.573147] register_blkdev, hello_major=252
Jul 25 13:59:45 ub18 kernel: [116444.573149] hello_disk_devices=0x00000000d76c9fb3
Jul 25 13:59:45 ub18 kernel: [116444.573150] hello_setup_device, which=0, dev=0x00000000d76c9fb3
Jul 25 13:59:45 ub18 kernel: [116444.573240] blk_alloc_queue=0x000000008c4cc732
Jul 25 13:59:45 ub18 kernel: [116444.573244] alloc_disk, dev->gd=0x000000007d1548c3
Jul 25 13:59:45 ub18 kernel: [116444.573245] add_disk start, which=0
Jul 25 13:59:45 ub18 kernel: [116444.579108] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000006f3f4553
Jul 25 13:59:45 ub18 kernel: [116444.579111] hello_disk_xfer_bio start
Jul 25 13:59:45 ub18 kernel: [116444.579113] bio_for_each_segment, iter=0x0000000059c7896e
Jul 25 13:59:45 ub18 kernel: [116444.579114] sector=0, nsect=8, buffer=0x000000009926e043, is_write=0
Jul 25 13:59:45 ub18 kernel: [116444.579116] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 13:59:45 ub18 kernel: [116444.579118] hello_disk_xfer_bio end
Jul 25 13:59:45 ub18 kernel: [116444.579124] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000006f3f4553
Jul 25 13:59:45 ub18 kernel: [116444.579125] hello_disk_xfer_bio start
Jul 25 13:59:45 ub18 kernel: [116444.579127] bio_for_each_segment, iter=0x000000007baf5dec
Jul 25 13:59:45 ub18 kernel: [116444.579128] sector=8, nsect=8, buffer=0x00000000e6cc6e45, is_write=0
Jul 25 13:59:45 ub18 kernel: [116444.579129] hello_disk_transfer, offset=4096, nbytes=4096
Jul 25 13:59:45 ub18 kernel: [116444.579131] hello_disk_xfer_bio end
Jul 25 13:59:45 ub18 kernel: [116444.579136] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000006f3f4553
Jul 25 13:59:45 ub18 kernel: [116444.579137] hello_disk_xfer_bio start
Jul 25 13:59:45 ub18 kernel: [116444.579138] bio_for_each_segment, iter=0x00000000cca1f4fa
Jul 25 13:59:45 ub18 kernel: [116444.579139] sector=24, nsect=8, buffer=0x00000000a65caa84, is_write=0
Jul 25 13:59:45 ub18 kernel: [116444.579141] hello_disk_transfer, offset=12288, nbytes=4096
Jul 25 13:59:45 ub18 kernel: [116444.579142] hello_disk_xfer_bio end
Jul 25 13:59:45 ub18 kernel: [116444.579247] add_disk end, which=0


$ sudo mkfs.ext4 /dev/hello_diska

dmesg info
Jul 25 14:01:08 ub18 kernel: [116527.719301] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719304] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719305] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719306] sector=8, nsect=8, buffer=0x00000000fea48bac, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719307] hello_disk_transfer, offset=4096, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719309] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719316] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719317] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719318] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719319] sector=0, nsect=8, buffer=0x000000008f1d3078, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719320] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719321] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719327] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719328] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719329] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719330] sector=24, nsect=8, buffer=0x00000000cce99009, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719332] hello_disk_transfer, offset=12288, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719333] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719336] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719337] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719338] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719339] sector=56, nsect=8, buffer=0x00000000f8ecfced, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719340] hello_disk_transfer, offset=28672, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719341] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719344] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719345] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719346] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719347] sector=120, nsect=8, buffer=0x00000000a2eac9c3, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719348] hello_disk_transfer, offset=61440, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719349] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719357] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719358] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719358] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719360] sector=16, nsect=8, buffer=0x000000005a0e8c73, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719361] hello_disk_transfer, offset=8192, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719362] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719366] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719367] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719368] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719370] sector=128, nsect=8, buffer=0x000000001bcd79aa, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719371] hello_disk_transfer, offset=65536, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719372] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719380] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719381] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719382] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719383] sector=64, nsect=8, buffer=0x000000001f3fd0bd, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719384] hello_disk_transfer, offset=32768, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719385] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719395] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719396] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719397] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719398] sector=512, nsect=8, buffer=0x0000000094829d7e, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719399] hello_disk_transfer, offset=262144, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719400] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719405] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719406] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719407] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719408] sector=32, nsect=8, buffer=0x00000000767fdfc9, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719409] hello_disk_transfer, offset=16384, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719410] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719449] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719450] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719451] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719452] sector=0, nsect=8, buffer=0x000000008f1d3078, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719453] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719454] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.719458] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.719459] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.719460] bio_for_each_segment, iter=0x000000000b9037a1
Jul 25 14:01:08 ub18 kernel: [116527.719461] sector=24, nsect=8, buffer=0x00000000fea48bac, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.719462] hello_disk_transfer, offset=12288, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.719463] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.720031] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.720033] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.720034] bio_for_each_segment, iter=0x00000000daa1dbb0
Jul 25 14:01:08 ub18 kernel: [116527.720035] sector=0, nsect=8, buffer=0x000000008f1d3078, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.720036] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.720037] bio_for_each_segment, iter=0x00000000daa1dbb0
Jul 25 14:01:08 ub18 kernel: [116527.720038] sector=0, nsect=8, buffer=0x00000000fea48bac, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.720039] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.720040] bio_for_each_segment, iter=0x00000000daa1dbb0
Jul 25 14:01:08 ub18 kernel: [116527.720041] sector=0, nsect=8, buffer=0x000000005a0e8c73, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.720042] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.720043] bio_for_each_segment, iter=0x00000000daa1dbb0
Jul 25 14:01:08 ub18 kernel: [116527.720045] sector=0, nsect=8, buffer=0x00000000cce99009, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.720046] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.720047] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.720345] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.720347] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.720347] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.720349] sector=0, nsect=8, buffer=0x000000008f1d3078, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.720350] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.720351] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.726339] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.726342] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.726344] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.726346] sector=16, nsect=8, buffer=0x00000000ba1b347c, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.726347] hello_disk_transfer, offset=8192, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.726349] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.726361] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.726362] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.726363] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.726365] sector=72, nsect=8, buffer=0x0000000057c21a24, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.726367] hello_disk_transfer, offset=36864, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.726368] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.726376] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.726377] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.726378] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.726380] sector=8, nsect=8, buffer=0x0000000023c55df2, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.726381] hello_disk_transfer, offset=4096, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.726386] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.726420] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.726422] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.726423] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.726425] sector=24, nsect=8, buffer=0x0000000004a30f4c, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.726426] hello_disk_transfer, offset=12288, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.726428] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.726447] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.726448] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.726449] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.726451] sector=32, nsect=8, buffer=0x00000000b3de9501, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.726452] hello_disk_transfer, offset=16384, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.726454] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.727330] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.727333] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.727335] bio_for_each_segment, iter=0x0000000065c1a0f8
Jul 25 14:01:08 ub18 kernel: [116527.727337] sector=40, nsect=8, buffer=0x00000000f2060743, is_write=0
Jul 25 14:01:08 ub18 kernel: [116527.727338] hello_disk_transfer, offset=20480, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.727396] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.727419] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.727420] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.727422] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.727424] sector=0, nsect=8, buffer=0x000000008f1d3078, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.727425] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.727427] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.727431] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.727433] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.727434] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.727436] sector=8, nsect=8, buffer=0x0000000023c55df2, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.727437] hello_disk_transfer, offset=4096, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.727439] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.727442] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.727443] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.727445] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.727446] sector=16, nsect=8, buffer=0x00000000ba1b347c, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.727448] hello_disk_transfer, offset=8192, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.727450] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.727453] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.727454] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.727455] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.727457] sector=24, nsect=8, buffer=0x0000000004a30f4c, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.727459] hello_disk_transfer, offset=12288, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.727461] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728018] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728020] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728021] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728023] sector=32, nsect=8, buffer=0x00000000b3de9501, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728025] hello_disk_transfer, offset=16384, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728026] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728029] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728031] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728032] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728034] sector=40, nsect=8, buffer=0x00000000f2060743, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728035] hello_disk_transfer, offset=20480, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728037] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728040] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728041] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728042] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728044] sector=72, nsect=8, buffer=0x0000000057c21a24, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728046] hello_disk_transfer, offset=36864, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728079] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728082] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728083] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728085] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728086] sector=896, nsect=8, buffer=0x0000000094829d7e, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728088] hello_disk_transfer, offset=458752, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728090] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728092] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728093] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728095] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728119] sector=904, nsect=8, buffer=0x00000000c8461e06, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728120] hello_disk_transfer, offset=462848, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728122] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728125] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728126] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728143] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728145] sector=912, nsect=8, buffer=0x00000000e8f32122, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728146] hello_disk_transfer, offset=466944, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728149] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728172] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728174] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728175] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728177] sector=920, nsect=8, buffer=0x000000003f576e57, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728178] hello_disk_transfer, offset=471040, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728180] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728199] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728200] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728201] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728203] sector=928, nsect=8, buffer=0x00000000204e24de, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728204] hello_disk_transfer, offset=475136, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728206] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728209] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728210] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728211] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728213] sector=936, nsect=8, buffer=0x00000000add0ff69, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728214] hello_disk_transfer, offset=479232, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728216] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728219] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728220] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728241] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728242] sector=944, nsect=8, buffer=0x000000005deaee9e, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728244] hello_disk_transfer, offset=483328, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728246] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728252] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728253] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728254] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728256] sector=952, nsect=8, buffer=0x0000000054fe1d81, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728257] hello_disk_transfer, offset=487424, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728259] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728262] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728264] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728265] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728267] sector=960, nsect=8, buffer=0x00000000fde62c03, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728268] hello_disk_transfer, offset=491520, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728270] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728273] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728274] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728275] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728277] sector=968, nsect=8, buffer=0x0000000048bc3ac9, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728278] hello_disk_transfer, offset=495616, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728280] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728283] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728284] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728285] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728287] sector=976, nsect=8, buffer=0x000000003f826300, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728289] hello_disk_transfer, offset=499712, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728290] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728293] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728294] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728296] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728297] sector=984, nsect=8, buffer=0x000000005c9796ee, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728299] hello_disk_transfer, offset=503808, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728301] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728320] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728321] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728322] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728324] sector=992, nsect=8, buffer=0x00000000af35f09c, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728325] hello_disk_transfer, offset=507904, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728346] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728349] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728351] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728352] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728354] sector=1000, nsect=8, buffer=0x000000000693bd1b, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728355] hello_disk_transfer, offset=512000, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728357] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728360] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728361] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728363] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728364] sector=1008, nsect=8, buffer=0x00000000fd331ac7, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728366] hello_disk_transfer, offset=516096, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728368] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728371] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728372] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728373] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728375] sector=1016, nsect=8, buffer=0x00000000a14ec306, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728376] hello_disk_transfer, offset=520192, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728378] hello_disk_xfer_bio end
Jul 25 14:01:08 ub18 kernel: [116527.728389] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000008cdb4c04
Jul 25 14:01:08 ub18 kernel: [116527.728391] hello_disk_xfer_bio start
Jul 25 14:01:08 ub18 kernel: [116527.728392] bio_for_each_segment, iter=0x000000007be68881
Jul 25 14:01:08 ub18 kernel: [116527.728394] sector=0, nsect=8, buffer=0x000000008f1d3078, is_write=1
Jul 25 14:01:08 ub18 kernel: [116527.728395] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:01:08 ub18 kernel: [116527.728397] hello_disk_xfer_bio end

$ sudo mount /dev/hello_diska xxx

dmesg info
Jul 25 14:03:12 ub18 kernel: [116650.939814] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.939818] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.939819] bio_for_each_segment, iter=0x00000000a42dbe9f
Jul 25 14:03:12 ub18 kernel: [116650.939821] sector=8, nsect=8, buffer=0x00000000f5670d8e, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.939822] hello_disk_transfer, offset=4096, nbytes=4096
Jul 25 14:03:12 ub18 kernel: [116650.939823] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.939831] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.939832] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.939833] bio_for_each_segment, iter=0x00000000a42dbe9f
Jul 25 14:03:12 ub18 kernel: [116650.939854] sector=0, nsect=8, buffer=0x00000000e6f91e9f, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.939856] hello_disk_transfer, offset=0, nbytes=4096
Jul 25 14:03:12 ub18 kernel: [116650.939857] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.939868] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.939869] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.939870] bio_for_each_segment, iter=0x00000000a42dbe9f
Jul 25 14:03:12 ub18 kernel: [116650.939871] sector=24, nsect=8, buffer=0x00000000cb104bbb, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.939872] hello_disk_transfer, offset=12288, nbytes=4096
Jul 25 14:03:12 ub18 kernel: [116650.939874] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.939877] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.939878] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.939879] bio_for_each_segment, iter=0x00000000a42dbe9f
Jul 25 14:03:12 ub18 kernel: [116650.939880] sector=56, nsect=8, buffer=0x00000000d3b8cf23, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.939881] hello_disk_transfer, offset=28672, nbytes=4096
Jul 25 14:03:12 ub18 kernel: [116650.939883] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.939886] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.939887] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.939888] bio_for_each_segment, iter=0x00000000a42dbe9f
Jul 25 14:03:12 ub18 kernel: [116650.939889] sector=120, nsect=8, buffer=0x00000000b94e16e3, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.939890] hello_disk_transfer, offset=61440, nbytes=4096
Jul 25 14:03:12 ub18 kernel: [116650.939893] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.939999] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.940000] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.940017] bio_for_each_segment, iter=0x00000000e2ab4bb3
Jul 25 14:03:12 ub18 kernel: [116650.940019] sector=2, nsect=2, buffer=0x00000000960d08ab, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.940020] hello_disk_transfer, offset=1024, nbytes=1024
Jul 25 14:03:12 ub18 kernel: [116650.940021] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.940074] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x000000002a86969c
Jul 25 14:03:12 ub18 kernel: [116650.940075] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.940076] bio_for_each_segment, iter=0x000000005f68af84
Jul 25 14:03:12 ub18 kernel: [116650.940077] sector=4, nsect=2, buffer=0x000000004d524312, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.940079] hello_disk_transfer, offset=2048, nbytes=1024
Jul 25 14:03:12 ub18 kernel: [116650.940080] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.940249] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000993aa32a
Jul 25 14:03:12 ub18 kernel: [116650.940250] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.940251] bio_for_each_segment, iter=0x00000000a5a95209
Jul 25 14:03:12 ub18 kernel: [116650.940253] sector=78, nsect=2, buffer=0x000000002f9bfd58, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.940254] hello_disk_transfer, offset=39936, nbytes=1024
Jul 25 14:03:12 ub18 kernel: [116650.940255] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.940257] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000993aa32a
Jul 25 14:03:12 ub18 kernel: [116650.940258] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.940258] bio_for_each_segment, iter=0x00000000272fad7c
Jul 25 14:03:12 ub18 kernel: [116650.940260] sector=76, nsect=2, buffer=0x000000009cf5a76f, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.940261] hello_disk_transfer, offset=38912, nbytes=1024
Jul 25 14:03:12 ub18 kernel: [116650.940262] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.940269] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000993aa32a
Jul 25 14:03:12 ub18 kernel: [116650.940270] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.940271] bio_for_each_segment, iter=0x00000000a09e4844
Jul 25 14:03:12 ub18 kernel: [116650.940272] sector=2, nsect=2, buffer=0x00000000960d08ab, is_write=1
Jul 25 14:03:12 ub18 kernel: [116650.940273] hello_disk_transfer, offset=1024, nbytes=1024
Jul 25 14:03:12 ub18 kernel: [116650.940274] hello_disk_xfer_bio end
Jul 25 14:03:12 ub18 kernel: [116650.940311] EXT4-fs (hello_diska): mounted filesystem without journal. Opts: (null)
Jul 25 14:03:12 ub18 kernel: [116650.950365] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000037f24e4f
Jul 25 14:03:12 ub18 kernel: [116650.950367] hello_disk_xfer_bio start
Jul 25 14:03:12 ub18 kernel: [116650.950368] bio_for_each_segment, iter=0x00000000649c1189
Jul 25 14:03:12 ub18 kernel: [116650.950370] sector=14, nsect=2, buffer=0x00000000077bfb35, is_write=0
Jul 25 14:03:12 ub18 kernel: [116650.950371] hello_disk_transfer, offset=7168, nbytes=1024
Jul 25 14:03:12 ub18 kernel: [116650.950372] hello_disk_xfer_bio end
Jul 25 14:03:13 ub18 kernel: [116652.436985] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000b43d4271
Jul 25 14:03:13 ub18 kernel: [116652.436988] hello_disk_xfer_bio start
Jul 25 14:03:13 ub18 kernel: [116652.436989] bio_for_each_segment, iter=0x00000000698cf9e6
Jul 25 14:03:13 ub18 kernel: [116652.436991] sector=80, nsect=8, buffer=0x000000000932f201, is_write=1
Jul 25 14:03:13 ub18 kernel: [116652.436992] hello_disk_transfer, offset=40960, nbytes=4096
Jul 25 14:03:13 ub18 kernel: [116652.436994] bio_for_each_segment, iter=0x00000000698cf9e6
Jul 25 14:03:13 ub18 kernel: [116652.436995] sector=80, nsect=8, buffer=0x000000000932f201, is_write=1
Jul 25 14:03:13 ub18 kernel: [116652.436996] hello_disk_transfer, offset=40960, nbytes=4096
Jul 25 14:03:13 ub18 kernel: [116652.436997] hello_disk_xfer_bio end
Jul 25 14:03:42 ub18 kernel: [116681.716853] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000e3c7baff
Jul 25 14:03:42 ub18 kernel: [116681.716863] hello_disk_xfer_bio start
Jul 25 14:03:42 ub18 kernel: [116681.716869] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:03:42 ub18 kernel: [116681.716876] sector=4, nsect=2, buffer=0x000000004d524312, is_write=1
Jul 25 14:03:42 ub18 kernel: [116681.716881] hello_disk_transfer, offset=2048, nbytes=1024
Jul 25 14:03:42 ub18 kernel: [116681.716887] hello_disk_xfer_bio end
Jul 25 14:03:42 ub18 kernel: [116681.716901] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000e3c7baff
Jul 25 14:03:42 ub18 kernel: [116681.716905] hello_disk_xfer_bio start
Jul 25 14:03:42 ub18 kernel: [116681.716910] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:03:42 ub18 kernel: [116681.716916] sector=76, nsect=2, buffer=0x000000009cf5a76f, is_write=1
Jul 25 14:03:42 ub18 kernel: [116681.716921] hello_disk_transfer, offset=38912, nbytes=1024
Jul 25 14:03:42 ub18 kernel: [116681.716926] hello_disk_xfer_bio end


$ sudo cp hello_64bit.c xxx

dmesg info
Jul 25 14:05:30 ub18 kernel: [116789.482650] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000020f7a2e6
Jul 25 14:05:30 ub18 kernel: [116789.482653] hello_disk_xfer_bio start
Jul 25 14:05:30 ub18 kernel: [116789.482654] bio_for_each_segment, iter=0x00000000065f36f7
Jul 25 14:05:30 ub18 kernel: [116789.482655] sector=44, nsect=2, buffer=0x00000000ea1dd391, is_write=0
Jul 25 14:05:30 ub18 kernel: [116789.482656] hello_disk_transfer, offset=22528, nbytes=1024
Jul 25 14:05:30 ub18 kernel: [116789.482658] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.211952] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.211954] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.211955] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:01 ub18 kernel: [116820.211957] sector=76, nsect=2, buffer=0x000000009cf5a76f, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.211958] hello_disk_transfer, offset=38912, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.211959] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.211961] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.211962] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.211963] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:01 ub18 kernel: [116820.211964] sector=78, nsect=2, buffer=0x000000002f9bfd58, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.211965] hello_disk_transfer, offset=39936, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.211966] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.211970] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.211971] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.211972] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:01 ub18 kernel: [116820.211973] sector=2, nsect=2, buffer=0x00000000960d08ab, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.211974] hello_disk_transfer, offset=1024, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.211975] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.211976] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.211977] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.211978] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:01 ub18 kernel: [116820.211979] sector=4, nsect=2, buffer=0x000000004d524312, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.211980] hello_disk_transfer, offset=2048, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.211981] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.211983] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.211984] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.211985] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:01 ub18 kernel: [116820.211986] sector=14, nsect=2, buffer=0x00000000077bfb35, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.211987] hello_disk_transfer, offset=7168, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.211988] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.211990] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.211991] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.211991] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:01 ub18 kernel: [116820.211992] sector=44, nsect=2, buffer=0x00000000ea1dd391, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.211993] hello_disk_transfer, offset=22528, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.211995] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.212007] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.212008] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.212009] bio_for_each_segment, iter=0x00000000ccac0538
Jul 25 14:06:01 ub18 kernel: [116820.212010] sector=12, nsect=2, buffer=0x00000000557cf6c0, is_write=0
Jul 25 14:06:01 ub18 kernel: [116820.212011] hello_disk_transfer, offset=6144, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.212012] hello_disk_xfer_bio end
Jul 25 14:06:01 ub18 kernel: [116820.212025] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:06:01 ub18 kernel: [116820.212026] hello_disk_xfer_bio start
Jul 25 14:06:01 ub18 kernel: [116820.212027] bio_for_each_segment, iter=0x00000000d8a8951f
Jul 25 14:06:01 ub18 kernel: [116820.212028] sector=42, nsect=2, buffer=0x0000000042ad711f, is_write=1
Jul 25 14:06:01 ub18 kernel: [116820.212029] hello_disk_transfer, offset=21504, nbytes=1024
Jul 25 14:06:01 ub18 kernel: [116820.212030] hello_disk_xfer_bio end
Jul 25 14:06:32 ub18 kernel: [116850.931852] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000020f7a2e6
Jul 25 14:06:32 ub18 kernel: [116850.931855] hello_disk_xfer_bio start
Jul 25 14:06:32 ub18 kernel: [116850.931856] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:32 ub18 kernel: [116850.931858] sector=78, nsect=2, buffer=0x000000002f9bfd58, is_write=1
Jul 25 14:06:32 ub18 kernel: [116850.931859] hello_disk_transfer, offset=39936, nbytes=1024
Jul 25 14:06:32 ub18 kernel: [116850.931860] hello_disk_xfer_bio end
Jul 25 14:06:32 ub18 kernel: [116850.931865] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000020f7a2e6
Jul 25 14:06:32 ub18 kernel: [116850.931866] hello_disk_xfer_bio start
Jul 25 14:06:32 ub18 kernel: [116850.931867] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:32 ub18 kernel: [116850.931869] sector=4, nsect=2, buffer=0x000000004d524312, is_write=1
Jul 25 14:06:32 ub18 kernel: [116850.931870] hello_disk_transfer, offset=2048, nbytes=1024
Jul 25 14:06:32 ub18 kernel: [116850.931871] hello_disk_xfer_bio end
Jul 25 14:06:32 ub18 kernel: [116850.931873] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000020f7a2e6
Jul 25 14:06:32 ub18 kernel: [116850.931874] hello_disk_xfer_bio start
Jul 25 14:06:32 ub18 kernel: [116850.931875] bio_for_each_segment, iter=0x000000005cc996c0
Jul 25 14:06:32 ub18 kernel: [116850.931877] sector=12, nsect=2, buffer=0x00000000557cf6c0, is_write=1
Jul 25 14:06:32 ub18 kernel: [116850.931878] hello_disk_transfer, offset=6144, nbytes=1024
Jul 25 14:06:32 ub18 kernel: [116850.931879] hello_disk_xfer_bio end


$ cat xxx/hello_64bit.c

dmesg info
Jul 25 14:08:13 ub18 kernel: [116952.562776] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000067735f66
Jul 25 14:08:13 ub18 kernel: [116952.562779] hello_disk_xfer_bio start
Jul 25 14:08:13 ub18 kernel: [116952.562780] bio_for_each_segment, iter=0x00000000fa02d516
Jul 25 14:08:13 ub18 kernel: [116952.562781] sector=76, nsect=2, buffer=0x000000009cf5a76f, is_write=1
Jul 25 14:08:13 ub18 kernel: [116952.562783] hello_disk_transfer, offset=38912, nbytes=1024
Jul 25 14:08:13 ub18 kernel: [116952.562784] hello_disk_xfer_bio end
Jul 25 14:08:13 ub18 kernel: [116952.562786] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x0000000067735f66
Jul 25 14:08:13 ub18 kernel: [116952.562787] hello_disk_xfer_bio start
Jul 25 14:08:13 ub18 kernel: [116952.562788] bio_for_each_segment, iter=0x00000000fa02d516
Jul 25 14:08:13 ub18 kernel: [116952.562789] sector=78, nsect=2, buffer=0x000000002f9bfd58, is_write=1
Jul 25 14:08:13 ub18 kernel: [116952.562790] hello_disk_transfer, offset=39936, nbytes=1024
Jul 25 14:08:13 ub18 kernel: [116952.562791] hello_disk_xfer_bio end


$ sudo umount xxx

dmesg info
Jul 25 14:09:16 ub18 kernel: [117015.633358] hello_disk_make_request, request_queue=0x000000008c4cc732, bio=0x00000000cfac5e91
Jul 25 14:09:16 ub18 kernel: [117015.633360] hello_disk_xfer_bio start
Jul 25 14:09:16 ub18 kernel: [117015.633361] bio_for_each_segment, iter=0x00000000cc9a1fa9
Jul 25 14:09:16 ub18 kernel: [117015.633363] sector=2, nsect=2, buffer=0x00000000960d08ab, is_write=1
Jul 25 14:09:16 ub18 kernel: [117015.633364] hello_disk_transfer, offset=1024, nbytes=1024
Jul 25 14:09:16 ub18 kernel: [117015.633365] hello_disk_xfer_bio end


$ sudo rmmod hello_disk

dmesg info
Jul 25 14:09:56 ub18 kernel: [117055.276762] hello_disk_exit
Jul 25 14:09:56 ub18 kernel: [117055.291274] i=0, del_gendisk and put_disk
Jul 25 14:09:56 ub18 kernel: [117055.291284] i=0, kobject_put
Jul 25 14:09:56 ub18 kernel: [117055.291624] unregister_blkdev and kfree
