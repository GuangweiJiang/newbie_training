KVERS = $(shell uname -r)
# Kernel modules
obj-m +=linux2.o

# Specify flags for the module compilation.
#EXTER_CFLAGS=-g -o0

build: kernel_modules

kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules

clean:
	make -C /lib/modulea/$(KVERS)/BUILD M=$(CURDIR) clean
