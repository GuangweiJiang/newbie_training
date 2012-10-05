/*
 * * file name: write_t.c
 * * purpose: a test program of module ex_02
 * * creator: Allan xing
 * * create time: 2012-09-17
 * * modify history: 2012-10-05 Code optimization
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <linux/ioctl.h>

#define IOCTL_CHARDEV_MAGIC 'k'
#define IOCTL_CHARDEV_MAX_NR 2

#define IOCTL_CHARDEV_CLEAR _IO(IOCTL_CHARDEV_MAGIC,1)
#define IOCTL_CHARDEV_OFFSET _IO(IOCTL_CHARDEV_MAGIC,2)

int main(int argc,char** argv)
{
	int fd;
	char buf[20];
	if(argc<3)
	{
		fprintf(stderr,"Usage:%s\n",strerror(errno));
		exit(0);
	}
	
	if((fd=open(argv[1],O_RDWR | O_NONBLOCK | O_ASYNC))<0)
	{
		fprintf(stderr,"open file error:%s\n",strerror(errno));
		exit(0);
	}
	write(fd,argv[2],strlen(argv[2]));
	printf("write: str= %s\n",argv[2]);

	ioctl(fd,IOCTL_CHARDEV_OFFSET,-10);

	memset(buf,0,sizeof(buf));
	read(fd,buf,strlen(argv[2]));
	printf("read: %s\n",buf);
	close(fd);
	return 0;
}
