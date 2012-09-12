/*
 * file name: ex01.c
 * purpose: One file contains n positive integer, and n = 10^7th power;
 *          file sorted in ascending order.
 *creator: Allan xing
 *create time: 2012-09-12
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <time.h>

#define N 1000000

//Data exchange
void swap(int *p, int *q)
{
	int t;
	t=*p;
	*p=*q;
	*q=t;
}
//sort data
void quicksort(int p[],int start,int end)
{
	int i,j,center;
	if(start<end){
		center=(start+end)/2;
		i=start-1;
		j=end+1;
		while(1){
			while(p[++i]<p[center]);
			while(p[center]<p[--j]);
			if(i>=j)
				break;
			swap(&p[i],&p[j]);
		}
		quicksort(p,start,i-1);
		quicksort(p,j+1,end);
	}
}
//print data
void outsort(int *p,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%d ",p[i]);
	}
	printf("\n");
}

int main(void)
{
	clock_t begin,end;
	double cost;
	begin=clock();
	int num[N];
	int i,j;
//	for(j=0;j<10;j++)
//	{
		int *p=(int*)malloc(N*sizeof(int));
		for(i=0;i<N;i++)
			num[i]=rand()%456;
		quicksort(num,0,sizeof(num)/sizeof(int)-1);
		outsort(num,sizeof(num)/sizeof(int));
		free(p);
//	}
	end =clock();
	cost=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("%5.1lf seconds\n",cost);
	return 0;
}
