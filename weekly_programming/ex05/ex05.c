/*
 * file name: ex05.c
 * purpose: generates k random numbers
 * creator: Allan xing
 * create time: 2012-10-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>//malloc
#include <string.h>//memset

#define N 10000000
#define K 5000000
FILE *fd;

void swap(int *a, int *b)
{
	if(a!=b)
	{
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}

void generateDiffRand(int *a, int k, int n)
{
	int i;
	time_t t;

	for(i = 0;i < n;i++)
	{
		a[i] = i;
	}
	srand((int)time(&t));
	for(i = 0;i < k; i++)
	{
		swap(&a[i],&a[i+rand()%(n-i)]);
	}
}

void print_outdata(int *a, int m)
{
	int i;
	for(i = 0; i < m; i++)
	{
		fprintf(fd,"%5d ",a[i]);
	}
}

int main(void)
{
	int *a;
	if((fd = fopen("./file.txt","w+")) == NULL)
	{
		printf("open error!\n");
		exit(0);
	}
	a = (int*)malloc(N*sizeof(int));
	if(a == 0)return 0;
	memset(a,0,sizeof(a));

	generateDiffRand(a,K,N);
	print_outdata(a,K);
	return 0;
}

