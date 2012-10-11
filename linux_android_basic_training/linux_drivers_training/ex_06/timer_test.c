/*
 * file name: timer_test.c
 * purpose: a test file for ex_06.c
 * creator: Allan xing
 * create time: 2012-10-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	int counter = 0;
	int old_counter = 0;

	printf("It is a timer test,when the file was be opened for 10 seconds,it will be closed!\n");
	printf("loading.....\n");
	fd = open("/dev/timer",O_RDONLY);
	if(fd)
	{
		while(1)
		{
			read(fd,&counter,sizeof(unsigned int));
			if(counter != old_counter)
			{
				printf("%d seconds after open /dev/timer\n",counter);
				old_counter = counter;
			}	
			if(counter >= 10)
			{
				printf("It was closed!\n");
				close(fd);
				exit(0);
			}
		}
	}
	else
	{
		printf("open file failure!\n");
	}
	return 0;
}


