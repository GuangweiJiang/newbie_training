//==========================================
// Filename:
// chardriver
//
// Copyright (C) 2006 Wistron
// All rights reserved.
//
// Description:
//  
//
// Author/Created Date:
// Jimmy Jiang, 7.28'14
//
// Modification History:
//
// open driver node,then write some word to it for test concurrency 
// and race conditions
// Note:
//
//==========================================
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define MEM_CLEAR 0x100004
#define MEM_SET   0x100005
int main(void)
{
	int fd,i,a;
	fd=open("/dev/globalmem_dev",O_RDWR);
	if(fd == -1)
	{
		printf("fail to open file\n");
		return -1;
	}
	printf("输入数字1或2：1为输入，2为清除\n");
	scanf("%d",&a);
	switch(a)	
	{
	case 1:
	{
		if((write(fd,"jiang",sizeof("jiang")))<=0);
		{
			printf("fail to write number\n");
			return -1;
		}
		printf("success\n");
	}break;
	case 2:
		ioctl(fd,MEM_CLEAR);
		break;
    	}
	close(fd);
	return 0;
}
