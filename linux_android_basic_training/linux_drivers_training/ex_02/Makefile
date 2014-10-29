KVERS = $(shell uname -r)
# Kernel modules
obj-m +=linux222.o
PWD=$(shell pwd)
# Specify flags for the module compilation.
#EXTER_CFLAGS=-g -o0

build: kernel_modules

kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD)	 clean
