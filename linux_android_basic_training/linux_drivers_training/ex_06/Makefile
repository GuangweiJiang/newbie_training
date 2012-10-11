#file name: Makefile
#description: a file to make the file of ex_06.c
#creator: Allan xing
#create time: 2012-10-10

obj-m +=ex_06.o
KVER = $(shell uname -r)
PWD  = $(shell pwd)
KDIR = /usr/src/linux-headers-$(KVER)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
