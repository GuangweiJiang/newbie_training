/*
 * * file name: write_t.c
 * * purpose: a test program of module ex_02
 * * creator: Allan xing
 * * create time: 2012-09-17
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc,char** argv)
{
	if(argc<3){
		fprintf(stderr,"Usage:%s\n",strerror(errno));
		exit(0);
	}
	int fd;
	if((fd=open(argv[1],O_RDWR | O_NONBLOCK | O_ASYNC))<0){
		fprintf(stderr,"open file error:%s\n",strerror(errno));
		exit(0);
	}
	write(fd,argv[2],strlen(argv[2]));
	printf("write: str= %s\n",argv[2]);
	close(fd);
	return 0;
}
