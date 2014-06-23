
#hello_makefile

obj-m :=hello.o     
KVER=$(shell uname -r)
KERNELDIR=/usr/src/linux-headers-${KVER}
PWD=$(shell pwd)

all:

	make -C $(KERNELDIR) M=$(PWD) modules

	

.PHONY :clean

clean:

	rm -rf *.o *ko

