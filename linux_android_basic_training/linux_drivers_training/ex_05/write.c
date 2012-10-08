/*
 * file name: write.c
 * purpose: a test file for ex05
 * creator: Allan xing
 * create time: 2012-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int fd;
	if(argc < 3)
	{
		fprintf(stderr, "command error\n");
		exit(0);
	}
	if((fd = open(argv[1], O_RDWR)) < 0)
	{
		fprintf(stderr, "open file err\n");
		exit(0);
	}
	sleep(5);
	write(fd, argv[2], strlen(argv[2]));
	printf("write: str=%s\n", argv[2]);
	close(fd);
	return 0;
}
