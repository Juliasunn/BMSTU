obj-m += md1.o
obj-m += md2.o
obj-m += md3.o

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) $@

clean: 
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.* 
	@rm -fR .tmp* 
	@rm -rf .tmp_versions 
