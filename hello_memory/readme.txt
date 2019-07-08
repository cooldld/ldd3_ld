linux内存管理的示例

journalctl -f
or
sudo tail -f /var/log/syslog

make

sudo insmod hello.ko

sudo rmmod hello

make clean

kmalloc/__get_free_pages/vmalloc都是申请100K的内存空间

Jul  8 15:07:50 ub18 kernel: [ 4065.130814] kmalloc GFP_KERNEL, ptr=0x0000000010b83eeb, phys_addr=0x00000000e7ca8154
Jul  8 15:07:50 ub18 kernel: [ 4065.130817] kmalloc GFP_USER, ptr=0x000000009062c33c, phys_addr=0x00000000b82936a6
Jul  8 15:07:50 ub18 kernel: [ 4065.130819] kmalloc GFP_HIGHUSER, ptr=0x000000004fcab727, phys_addr=0x00000000674da60e
Jul  8 15:07:50 ub18 kernel: [ 4065.130829] kmalloc GFP_DMA, ptr=0x0000000060b7ffeb, phys_addr=0x000000003a05dfca
Jul  8 15:07:50 ub18 kernel: [ 4065.130831] __get_free_pages GFP_KERNEL, ptr=0x000000003d26c9fa, phys_addr=0x000000003b64212d
Jul  8 15:07:50 ub18 kernel: [ 4065.130834] __get_free_pages GFP_USER, ptr=0x00000000b53a0c6a, phys_addr=0x000000007f94cab2
Jul  8 15:07:50 ub18 kernel: [ 4065.130848] __get_free_pages GFP_HIGHUSER, ptr=0x00000000d5114d46, phys_addr=0x00000000b3dc13a2
Jul  8 15:07:50 ub18 kernel: [ 4065.130851] __get_free_pages GFP_DMA, ptr=0x000000002f31d7d5, phys_addr=0x00000000c030e812
Jul  8 15:07:50 ub18 kernel: [ 4065.130888] vmalloc, ptr=0x00000000a0444ebe, phys_addr=0x0000000057d99513
