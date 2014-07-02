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
#include <time.h>

/* MACROS */
#define	NUM		10000000
#define	SHIFT	5
#define MASK	0x1F

/* CONSTANTS AND VARIABLES */
int a[1 + NUM/32] = { 0 }; /* define an arry and initialize every element */

/* INTERNAL FUNCTIONS */
void setbit(int n)
{
	/* find the array member of bit n, and set flag */
	if (n > NUM){
		printf("too large\n");
		return ;
	}
	a[n >> SHIFT] |= 1 << (n & MASK); /* a[n/32] |= 1<<(n%32) */
}
int testbit(int n)
{
	/* if the n bit exist, resturn 1 */
	return a[n >> SHIFT] & (1 << ( n & MASK));
}

void show_time()
{
	time_t t = time(NULL);
	struct tm *mytm = localtime(&t);
	printf("%04d年%02d月%02d日 %02d:%02d:%02d t=%d\t", 
				mytm->tm_year+1900,	mytm->tm_mon+1, mytm->tm_mday, 
					mytm->tm_hour, mytm->tm_min, mytm->tm_sec, (int)t);
}
/* IMPLEMENTATION */
int main()
{
	/* open data.db and create file res.db to save the result of sorting */
	int fd1 = open("data.db", O_RDONLY);
	if (-1 == fd1) {
		perror("open");
		return -1;
	}

	/* read number of the file, and set flags */
	int i, n, res;
	show_time();
	printf("start to sorting %d nums...\n", NUM);
	for (i = 0; i <= NUM - 1; i++) {
		res = read(fd1, &n, sizeof(int));
		if (res == -1) {
			perror("read");
			return -1;
		} else if (res == 0) {
			break;
		}
		setbit(n); /* set flags */
	}

	/* traversal the array and write every element to res.db */
	int fd2 = open("res.db", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (-1 == fd2) {
		perror("open");
		return -1;
	}

	printf("writing to file...\n");
	for (i = 0; i <= NUM -1; i++) {
		if (testbit(i)) {
			write(fd2, &i, sizeof(int));
	//		printf("%d\t", i);
		}
	}
	show_time();
	printf("sorting over!\n");

	close(fd1);
	close(fd2);
	return 0;
}

