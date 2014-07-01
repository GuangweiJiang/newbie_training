/*
 *	filename:		user.c
 *	Description:	To test the char device driver
 *	Author:			Longbin Li <beangr@163.com>
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define SCULL_READ	0X10001
#define SCULL_WRITE	0X10002

int main(int argc, char *argv[]){
	int rdata;
	int wdata = 0x56;

	int fd = open("/dev/scull0", O_RDWR);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	char buf1[50] = "hello hello how are you";
	char buf2[50];

	write(fd, buf1, 50);
	lseek(fd, 0, SEEK_SET);
	read(fd, buf2, 50);
	printf("%s\n", buf2);
	lseek(fd, 0, SEEK_SET);

	ioctl(fd, SCULL_READ, &rdata);
	printf("read:%#x\n", rdata);
	sleep(1);

	printf("write:%#x\n", wdata);
	ioctl(fd, SCULL_WRITE, &wdata);
	sleep(1);

	return 0;
}
