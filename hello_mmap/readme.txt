ioremap和mmap的使用

Linux内核中ioremap映射的透彻理解
https://www.linuxidc.com/Linux/2011-04/34295.htm

!!!
Linux驱动mmap内存映射
https://www.cnblogs.com/wanghuaijun/p/7624564.html

linux库函数mmap()原理
https://blog.csdn.net/bbzhaohui/article/details/81665370

linux内存管理mmap函数详解
https://blog.csdn.net/notbaron/article/details/80019134

ioremap和mmap的调用流程
外设寄存器-->使用内存映射方式-->io内存物理地址-->内核调用ioremap()-->
-->映射到内核虚拟空间(3G~4G)-->readb()/writeb()内存读写-->
-->驱动程序调用mmap()-->映射到用户空间-->read()/write()内存读写

函数原型在mm/ioremap.c中
void *ioremap(unsigned long phys_addr, unsigned long size, unsigned long flags);
void iounmap(void *addr);

void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);

hello.c
在gmem_cdev/gmem1.c上加入mmap的使用

make
sudo insmod hello.ko
sudo mknod hello_dev c 243 0
sudo chmod 777 hello_dev

gcc mmap_test.c

$ ./a.out hello_dev
before mmap
after mmap, mapBuf=hello world

message info
Jul 10 14:17:32 ub18 kernel: [11925.581764] hello_init
Jul 10 14:17:32 ub18 kernel: [11925.581767] major=243, minor=0
Jul 10 14:17:32 ub18 kernel: [11925.581770] hello_data=0x00000000cdeb5302
Jul 10 14:17:32 ub18 kernel: [11925.581771] phys_addr=0x32ae4000
Jul 10 14:17:39 ub18 kernel: [11933.145274] hello_open
Jul 10 14:17:59 ub18 kernel: [11953.145612] hello_mmap
Jul 10 14:18:14 ub18 kernel: [11968.146955] hello_release
