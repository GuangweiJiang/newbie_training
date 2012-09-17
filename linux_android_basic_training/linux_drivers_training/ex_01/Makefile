#file name: Makefile
#purpose: compile ex_01.c
#creator: Allan xing
#create time: 2012-09-12

obj-m +=ex_01.o 						#生成目标文件
PWD  = $(shell pwd) 					#目标文件保存位置
KVER = $(shell uname -r)				#编译的内核版本号
KDIR = /usr/src/linux-headers-$(KVER)	#编译的内核路径
all:
		$(MAKE) -C $(KDIR) M=$(PWD) modules  #编译
clean:
		$(MAKE) -C $(KDIR) M=$(PWD) clean	#清除生成的文件
