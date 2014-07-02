/*
 * Filename:				generate.c
 *
 * Copyright (C) 2014 Wistron
 * All rights reserved.
 *
 * Description:				This file is to generate a random num from 0 to 10000000.
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
#include <stdlib.h>

/* MACROS */
#define	NUM		10000000
#define	SHIFT	5
#define MASK	0x1F

/* CONSTANTS AND VARIABLES */
int a[1 + NUM/32] = { 0 }; /* define an arry and initialize every member */

/* INTERNAL FUNCTIONS */
void setbit(int n)
{
	/* set flag */
	a[n >> SHIFT] |= 1 << (n & MASK); /* a[n/32] |= 1<<(n%32) */
}
void cl_bit(int n)
{
	/* clear flag */
	a[n >> SHIFT] &= ~(1 << (n & MASK)); /* a[n/32] |= 1<<(n%32) */
}
int testbit(int n)
{
	/* if the n bit exist, resturn 1 */
	return a[n >> SHIFT] & (1 << ( n & MASK));
}
int test_all_bit()
{
	int i, res;
	for(i = 0; i <= NUM/32; i++) {
		if (a[i]){
			return a[i];
		}
	}
	return a[i];
}
int list_bit(int n)
{
	int i = 0, j = 0;
	for (i = 0; i <= NUM - 1; i++) {
		if (testbit(i)){
			if (j == n) {
				return i;
			}
			j++;
		}
	}
	return i;
}

/* IMPLEMENTATION */
int main()
{
	/* create file data.db to save number */
	int fd1 = open("data.db", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (-1 == fd1) {
		perror("open");
		return -1;
	}

	/* read number of the file, and set flags */
	int i, res;
	for (i = 0; i <= NUM - 1; i++) {
		setbit(i); /* set flags */
	}

	srand(time(0));
	int n = NUM;
	int node;
	printf("starting to generate datas...\n");
	while (test_all_bit()) {
		if (n < 1000 ){
			node = rand() % n;
			i = list_bit(node);
		} else {
			i = rand() % NUM;
		}
		if (testbit(i)) {
			write(fd1, &i, sizeof(int));
			printf("%d\r", i);
			cl_bit(i);
			n--;
		}
	}
	printf("generated ok!\n");

	close(fd1);
	return 0;
}


