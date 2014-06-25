ifneq ($(KERNELRELEASE),)
obj-m += hello_kernel.o
else
KVERSION =$(shell uname -r)
KERNELDIR =/usr/src/linux-headers-$(KVERSION)

all:
	PWD=$(shell pwd)
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions module* Module*
endif
