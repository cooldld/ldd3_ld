KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += gmem0.o
obj-m += gmem1.o
obj-m += gmem2.o
obj-m += gmem3.o

modules:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	sudo rm gmem_dev* -f
