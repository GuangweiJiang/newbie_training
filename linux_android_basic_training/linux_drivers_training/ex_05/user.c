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

int main(int argc, char *argv[]){

	printf("pid = %d ......\n", getpid());

	pid_t pid = fork();
	if (pid != 0) {
		sleep(1);
	}
	int fd = open("/dev/scull0", O_RDWR);
	if (fd == -1) {
		perror("open");
		return -1;
	}
	printf("**open ok, pid = %d\n", getpid());
	printf("pid=%d is visiting the device\n", getpid());
	sleep(15);

	close(fd);
	printf("pid=%d exit, closing device\n", getpid());

	return 0;
}
