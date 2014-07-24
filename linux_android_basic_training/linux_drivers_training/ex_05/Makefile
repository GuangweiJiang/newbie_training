ifneq ($(KERNELRELEASE),)
	obj-m += chardrv.o
else
#	KERNELDIR=/opt/kernel
KVERSION=`uname -r`
KERNELDIR=/usr/src/linux-headers-$(KVERSION)

all:
	PWD=$(shell pwd)
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions module* Module*
endif
