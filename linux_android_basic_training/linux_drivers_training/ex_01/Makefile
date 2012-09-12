#file name: Makefile
#purpose: compile ex_01.c
#creator: Allan xing
#create time: 2012-09-12

obj-m +=ex_01.o
PWD  = $(shell pwd)
KVER = $(shell uname -r)
KDIR = /usr/src/linux-headers-$(KVER)
all:
		$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean
