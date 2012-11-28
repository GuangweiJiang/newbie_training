/*
 * file name: ex07.c
 * purpose: quick sort
 * creator: Allan xing
 * create time: 2012-11-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N  1000000

void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

void quicksort(int *a,int start,int end)
{
	int m = start;
	int i;
	if(start >= end)
		return;
	for(i = start+1; i <= end; i++)
	{
		if(a[i] < a[start])
		{
			swap(&a[++m],&a[i]);
		}
	}
	swap(&a[start],&a[m]);
	quicksort(a,start,m-1);
	quicksort(a,m+1,end);
}

void print_data(int *a,int size)
{
	int i;
	for(i = 0; i< size; i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}

int main(void)
{
	int i;
	clock_t begin,finish;
	double cost;
	int array[N];
	srand((unsigned)time(NULL));

	//1 random data
	for(i = 0; i < N; i++)
	{
		array[i]=rand()%123;
	}
	/*
	//2 Equivalent data
	for(i=0;i<N;i++)
	{
		array[i]=123;
	}
	
	//3 increasing data
	for(i = 0; i < N; i++)
	{
		array[i]=i;
	}
	*/
	begin=clock();
	quicksort(array,0,N-1);
	finish=clock();
	print_data(array,sizeof(array)/sizeof(int));
	cost=(double)(finish-begin)/CLOCKS_PER_SEC;
	printf("%5.1lf seconds\n",cost);
	return 0;
}
