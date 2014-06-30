/*
 * Filename:				sort.c
 *
 * Copyright (C) 2014 Wistron
 * All rights reserved.
 *
 * Description:				This file is a sort function.
 * Author/Created Date:		longbin Li, Jun25'14
 * Modification History:
 * Note:
 */

/* Include Files */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

/* MACROS */
#define	NUM		10000000
#define	SHIFT	5
#define MASK	0x1F

/* CONSTANTS AND VARIABLES */
unsigned int a[1 + NUM/32] = { 0 }; /* define an arry and initialize every member */

/* INTERNAL FUNCTIONS */
void setbit(int n)
{
	/* find the array member of bit n, and set flag */
	a[n >> SHIFT] |= 1 << (n & MASK); /* a[n/32] |= 1<<(n%32) */
}
int testbit(int n)
{
	/* if the n bit exist, resturn 1 */
	return a[n >> SHITF] & (1 << ( n & MASK));
}
/* IMPLEMENTATION */
int main()
{
	/* open data.db and create file res.db to save the result of sorting */
	int fd1 = open("data.db", O_RDONLY);
	if (-1 == fd) {
		perror("open");
		return -1;
	}
	int fd2 = open("res.db", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (-1 == fd2) {
		perror("open");
		return -1;
	}

	/* read number of the file, and set flags */
	int i, n;
	for (i = 0; i <= NUM -1; i++) {
		if (read(fd1, &n, sizeof(int)) == -1){
			perror("read");
			close(fd1);
			return -1;
		}
		setbit(n);
	}

	/* reposite the offset of the data.db to the head of the file */
	lseek(fd1, 0, SEEK_SET);

	/* traversal the array and write every element to res.db */
	for (i = 0; i <= NUM -1; i++) {
		if (read(fd1, &n, sizeof(int))){
			perror("read");
			close(fd1);
			return -1;
		}
		if (testbit(n)) {
			write(fd2, &n, sizeof(int));
		}
	}

	close(fd1);
	close(fd2);
	return 0;
}


