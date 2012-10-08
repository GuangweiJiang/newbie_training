#file name: Makefile
#description: a file to make the file of ex_05.c
#creator: Allan xing
#create time: 2012-10-08

obj-m +=ex_05.o
KVER = $(shell uname -r)
PWD  = $(shell pwd)
KDIR = /usr/src/linux-headers-$(KVER)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
