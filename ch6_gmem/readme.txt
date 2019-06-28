ch6 字符设备驱动

参考globalmem.c

gmem0.c
调用cdev api去注册、添加和删除字符设备，没有实现fops读写的功能
$ make
$ sudo insmod gmem0.ko
Jun 21 10:42:27 ub18 kernel: [79081.181809] gmem_init
Jun 21 10:42:27 ub18 kernel: [79081.181814] major=242, minor=0
$ sudo mknod gmem_dev c 242 0
$ cat gmem_dev
cat: gmem_dev: No such device or address
$ sudo echo hello > gmem_dev
zsh: permission denied: gmem_dev

gmem1.c
在gmem0.c上增加了file_operations的操作open/release/read/write/llseek
$ make
$ sudo insmod gmem1.ko
Jun 21 15:11:05 ub18 kernel: [95198.393437] gmem_init
Jun 21 15:11:05 ub18 kernel: [95198.393441] major=242, minor=0
$ sudo mknod gmem_dev c 242 0
$ sudo chmod 777 gmem_dev
$ echo hello > gmem_dev
$ cat gmem_dev
hello

gmem2.c
在gmem1.c上创建多个字符设备

gmem3.c
在gmem2.c上增加mutex的控制

gmem4.c
在gmem1.c上增加mutex和wait queue的控制
在一个终端执行写操作
$ echo "12345678901234567890" > gmem_dev
在另一个终端执行读操作
$ dd if=gmem_dev of=/dev/stdout bs=1 count=1
系统日志信息
Jun 27 16:12:53 ub18 kernel: [21870.913744] gmem_open
Jun 27 16:12:53 ub18 kernel: [21870.913749] gmem_llseek, offset=0, whence=1
Jun 27 16:12:53 ub18 kernel: [21870.914167] gmem_read, current len=10
Jun 27 16:12:53 ub18 kernel: [21870.914171] read count=1, len=9
Jun 27 16:12:53 ub18 kernel: [21870.914179] write, count=1
Jun 27 16:12:53 ub18 kernel: [21870.914184] gmem_write, current len=10
Jun 27 16:12:53 ub18 kernel: [21870.914326] gmem_release

gmem5.c
在gmem4.c上增加poll的操作
$ grep gmem /proc/devices
select_test.c用seletct api来验证
$ gcc select_test.c -o select_test
$ ./select_test gmem_dev
epoll_test.c用epoll api来验证
$ gcc epoll_test.c -o epoll_test
$ ./epoll_test gmem_dev
