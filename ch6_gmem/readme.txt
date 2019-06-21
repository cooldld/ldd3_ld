ch6 字符设备驱动

参考globalmem.c

gmem0.c
调用cdev api去注册、添加和删除字符设备，没有实现fops读写的功能
$ make
$ sudo insmod gmem0.ko
Jun 21 10:42:27 ub18 kernel: [79081.181809] gmem_init
Jun 21 10:42:27 ub18 kernel: [79081.181814] major=242, minor=0
$ sudo mknod gmem0_dev c 242 0
$ cat gmem0_dev 
cat: gmem0_dev: No such device or address
$ sudo echo hello > gmem0_dev 
zsh: permission denied: gmem0_dev

gmem1.c
增加了file_operations的操作open/release/read/write/llseek
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
创建多个字符设备
