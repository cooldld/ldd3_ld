KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += export_symbol.o
obj-m += hello.o

modules:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
