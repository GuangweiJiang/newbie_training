#globalmem_makefile

obj-m :=globalmem.o          
KVER=$(shell uname -r)
KERNELDIR=/usr/src/linux-headers-${KVER}  #set path
PWD=$(shell pwd)

all:

	make -C $(KERNELDIR) M=$(PWD) modules  #make under kernel

.PHONY :clean

clean:                          

	rm -rf *.o *.ko            # remove *.o or *.ko
