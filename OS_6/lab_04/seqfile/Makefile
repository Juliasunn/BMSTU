obj-m += new_segfile.o

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) $@
