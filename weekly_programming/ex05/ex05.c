/*
 * file name: ex05.c
 * purpose: generates k random numbers
 * creator: Allan xing
 * create time: 2012-10-23
 * modify history: Change global variables and add a new method
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>//malloc
#include <string.h>//memset

#define N 10000000
#define K 5000000

void swap(int *a, int *b)
{
	if(a!=b)
	{
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
	}
}

void generateDiffRand1(int *a, int k, int n)
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

//first:generate a array contain subscript second: extract randomly from it
void generateDiffRand2(int *a,int n)
{
	int *b = (int *)malloc(sizeof(int)*n);
	static int flag = 0;
	int i,index;
	for(i = 0;i < n; i++)
	{
		b[i] = i + 1;
	}
	if(!flag)
	{
		srand((int)time(0));
		flag = 1;
	}
	for(i = 0; i < n;i++)
	{
		index = rand() % n;
		if(b[index] != 0)
		{
			a[i] = b[index] - 1;
			b[index] = 0;
		}
	}
}

void print_outdata(FILE *fd,int *a, int m)
{
	int i;
	for(i = 0; i < m; i++)
	{
		fprintf(fd,"%5d ",a[i]);
	}
}

int main(void)
{
	FILE *fd;
	FILE *fd1;
	int *a;
	if((fd = fopen("./file.txt","w+")) == NULL)
	{
		printf("open error!\n");
		exit(0);
	}
	if((fd1 = fopen("./file1.txt","w+")) == NULL)
	{
		printf("open error!\n");
		exit(0);
	}
	a = (int*)malloc(N*sizeof(int));
	if(a == 0)return 0;
	memset(a,0,sizeof(a));

	generateDiffRand1(a,K,N);
	print_outdata(fd,a,K);

	generateDiffRand2(a,N);
	print_outdata(fd1,a,K);
	return 0;
}

