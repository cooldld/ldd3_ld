linux驱动: 如何向模块传递参数, module_param和module_param_array
https://www.cnblogs.com/mylinux/p/5670279.html

insmod 内核模块参数传递
https://www.cnblogs.com/lengbingshy/p/3909167.html

用默认值加载ko
sudo insmod hello.ko
hello, name=world, count=2, n_index=8
index[0]=0
index[1]=0
index[2]=0
index[3]=0
index[4]=0
index[5]=0
index[6]=0
index[7]=0
hello2 test
goodbye, name=world

用入参值加载ko
sudo insmod hello.ko name="wahaha" count="13" index=00,10,011
hello, name=wahaha, count=13, n_index=3
index[0]=0
index[1]=10
index[2]=9
goodbye, name=wahaha
