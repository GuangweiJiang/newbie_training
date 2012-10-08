/*
 * file name: read.c
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
	if(argc < 2)
	{
		fprintf(stderr, "command error\n");
		exit(0);
	}
	if((fd = open(argv[1], O_RDWR)) < 0)
	{
		fprintf(stderr, "open file err\n");
		exit(0);
	}
	char buf[10] = {'\0'};
	read(fd, buf, 5);
	printf("read: str=%s\n", buf);

	close(fd);
	return 0;
}
