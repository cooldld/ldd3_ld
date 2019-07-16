调用platform接口实现驱动和设备

在这个例子中，platform_match()函数是匹配设备名和驱动名

hello_driver.c
platform类型的驱动，驱动名是hello_platform

hello_device.c
platform类型的设备，设备名是hello_platform

$ make

$ sudo insmod hello_driver.ko

$ sudo insmod hello_device.ko

$ sudo rmmod hello_device

系统日志信息
ul 12 15:46:30 ub18 kernel: [15338.564672] hello_device_init
Jul 12 15:46:30 ub18 kernel: [15338.567465] hello_driver_probe
Jul 12 15:47:05 ub18 kernel: [15373.743917] hello_device_exit
Jul 12 15:47:05 ub18 kernel: [15373.743934] hello_driver_remove

hello_driver2.c
在hello_driver.c的基础上加入了misc设备注册和注销的处理

$ sudo insmod hello_driver2.ko

$ sudo insmod hello_device.ko

$ cat /proc/misc
 53 hello_miscdevice

$ ls /dev/hello_miscdevice
/dev/hello_miscdevice

$ sudo cat /dev/hello_miscdevice

$ sudo dd if=/dev/zero of=/dev/hello_miscdevice bs=1 count=1
dd: error writing '/dev/hello_miscdevice': No space left on device
1+0 records in
0+0 records out
0 bytes copied, 0.00115755 s, 0.0 kB/s

$ sudo rmmod hello_driver2

$ sudo rmmod hello_device

系统日志信息
Jul 16 10:38:59 ub18 kernel: [  147.382794] hello_driver2: loading out-of-tree module taints kernel.
Jul 16 10:39:40 ub18 kernel: [  188.605781] hello platform device init
Jul 16 10:39:40 ub18 kernel: [  188.607692] hello_driver_probe
Jul 16 10:39:40 ub18 kernel: [  188.607731] hello_platform hello_platform: hello_miscdevice register
Jul 16 10:40:33 ub18 kernel: [  241.069391] hello_open
Jul 16 10:40:33 ub18 kernel: [  241.069402] hello_read, f_pos=0
Jul 16 10:40:33 ub18 kernel: [  241.069409] hello_release
Jul 16 10:41:14 ub18 kernel: [  282.099787] hello_open
Jul 16 10:41:14 ub18 kernel: [  282.099796] hello_write, f_pos=0
Jul 16 10:41:14 ub18 kernel: [  282.100685] hello_release

Jul 16 10:42:11 ub18 kernel: [  339.663594] hello_driver_remove
Jul 16 10:42:11 ub18 kernel: [  339.665218] hello_platform hello_platform: hello_miscdevice deregister
Jul 16 10:42:16 ub18 kernel: [  343.969385] hello platform device exit
