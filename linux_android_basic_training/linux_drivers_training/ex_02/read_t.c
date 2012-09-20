/*
 *file name: read_t.c
 *purpose: a test program of module ex_02
 *creator: Allan xing
 *create time: 2012-09-20
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <memory.h>

int main(int argc, char** argv)
{
	if(argc<2){
		fprintf(stderr,"Usage: %s\n",strerror(errno));
		exit(0);
	}
	int fd;
	if((fd=open(argv[1],O_RDWR | O_NONBLOCK | O_ASYNC))<0){
		fprintf(stderr,"open file error:%s\n",strerror(errno));
		exit(0);
	}
	char buf[30];
	memset(buf,0,sizeof(buf));
	read(fd,buf,10);
	printf("read : %s\n",buf);
	close(fd);
	return 0;
}
