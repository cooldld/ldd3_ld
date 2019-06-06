all:
	make -C export_symbol
	make -C hello
	make -C hello_param
	make -C multi_obj
	make -C timer_test
	make -C ch6_gmem

clean:
	make clean -C export_symbol
	make clean -C hello
	make clean -C hello_param
	make clean -C multi_obj
	make clean -C timer_test
	make clean -C ch6_gmem
