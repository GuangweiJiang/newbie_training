ifneq ($(KERNELRELEASE),)
	obj-m += chardrv.o
else
	KVERSION=`uname -r`
	KERNELDIR=/usr/src/linux-headers-$(KVERSION)
	#KERNELDIR=/usr/src/linux-source-3.2.0/linux-source-3.2.0

all:
	PWD=$(shell pwd)
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions module* Module*
endif
