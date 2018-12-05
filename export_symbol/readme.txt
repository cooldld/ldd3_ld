insmod export_symbol.ko
insmod hello.ko

rmmod hello
rmmod export_symbol

Dec 05 15:18:19 ub18 kernel: call add_integar(2, 3)=5
Dec 05 15:18:19 ub18 kernel: call sub_integar(2, 3)=-1
Dec 05 15:18:26 ub18 kernel: hello_exit exit

