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
map_buf[0]=0x68
map_buf[1]=0x65
map_buf[2]=0x6c
map_buf[3]=0x6c
map_buf[4]=0x6f
map_buf[5]=0x20
map_buf[6]=0x77
map_buf[7]=0x6f
map_buf[8]=0x72
map_buf[9]=0x6c
map_buf[10]=0x64
map_buf[11]=0x0
map_buf[12]=0x0
map_buf[13]=0x0
map_buf[14]=0x0
map_buf[15]=0x0
map_buf=hello world

message info
Jul 12 13:59:14 ub18 kernel: [ 8902.661203] hello_init
Jul 12 13:59:14 ub18 kernel: [ 8902.661206] major=243, minor=0
Jul 12 13:59:25 ub18 kernel: [ 8914.084054] hello_open
Jul 12 13:59:25 ub18 kernel: [ 8914.084058] hello_data=0x000000000bcbba44
Jul 12 13:59:25 ub18 kernel: [ 8914.084059] hello_data=hello world
Jul 12 13:59:25 ub18 kernel: [ 8914.084060] phys_addr=0xce9a6000
Jul 12 13:59:25 ub18 kernel: [ 8914.084062] hello_mmap
Jul 12 13:59:26 ub18 kernel: [ 8915.088326] hello_release
