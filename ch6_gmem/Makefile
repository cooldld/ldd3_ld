KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += gmem0.o
obj-m += gmem1.o
obj-m += gmem2.o
obj-m += gmem3.o
obj-m += gmem4.o
obj-m += gmem5.o

modules:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
