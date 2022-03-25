obj-m += cookie_module.o


modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) $@
