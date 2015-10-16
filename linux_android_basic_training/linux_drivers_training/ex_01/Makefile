ifneq ($(KERNELRELEASE),)
	obj-m += hello_kernel.o
else
	KVERSION=`uname -r`
	KERNELDIR=/usr/src/linux-headers-$(KVERSION)

all:
	PWD=$(shell pwd)
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

.PHONY:clean
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions module* Module*
endif
