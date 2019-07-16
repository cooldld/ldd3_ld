all:
	make -C export_symbol
	make -C hello
	make -C hello_param
	make -C multi_obj
	make -C timer_test
	make -C gmem_cdev
	make -C hello_tasklet
	make -C hello_work_queue
	make -C hello_memory
	make -C hello_mmap
	make -C hello_platform

clean:
	make clean -C export_symbol
	make clean -C hello
	make clean -C hello_param
	make clean -C multi_obj
	make clean -C timer_test
	make clean -C gmem_cdev
	make clean -C hello_tasklet
	make clean -C hello_work_queue
	make clean -C hello_memory
	make clean -C hello_mmap
	make clean -C hello_platform
