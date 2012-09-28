#file name: Makefile
#purpose: compile ex_04.c
#creator: Allan xing
#create time: 2012-09-27

obj-m +=ex_04.o
PWD   =$(shell pwd)
KVER  =$(shell uname -r)
KDIR  = /usr/src/linux-headers-$(KVER)
all:
		make -C $(KDIR) M=$(PWD) modules
clean:
		make -C $(KDIR) M=$(PWD) clean
