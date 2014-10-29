//==========================================
// Filename:
//      testfile.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      This file is used to test the correctness of the device driver.
//
// Author/Created Date:
//      Jerry Liu, Jul.3rd 2013
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
//
//
int main(int argc, char **argv)
{
    	int fd = 0;
    	int num = 99;
    	char dev_name[128] ="/dev/ex02";
  	if(argc == 2)
    	{	
        	strcpy(dev_name,argv[1]);
    	}	
     	fd = open(dev_name, O_RDWR);
   	if(fd != -1)
    	{
        	printf("the first value is %d\n", num);
        	num = 1111;
        	write(fd, &num,sizeof(int));
        	read(fd, &num,sizeof(int));
       		printf("the second value is %d\n", num);
        	close(fd);
   	}
   	 else
   	{
       		printf("fail,the first value is %d;err=%s\n", num, strerror(errno));
    	}
    	return 0;
}


//----------------------------------------------------------------------------
// Function:
// 	    int main(int argc, char **argv)	     
//	
// Description:
//	    The function is used in user space to transfer the first number 99
//	    and the second number 1111 to the device driver.	
//		
