ifneq ($(KERNELRELEASE),)
	obj-m += chdrv.o
else
	KERNELDIR=/opt/kernel

all:
	PWD=$(shell pwd)
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions module* Module*
endif
