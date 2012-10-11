/*
 * file name: ex04.c
 * purpose: Insertion Sort
 * creator: Allan xing
 * create time: 2012-10-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N  100000

//Before optimization
void isort1(int *p,int size)
{
	int i,j;
	for(i=1;i<size;i++)
	{
		for(j=i;j>0&&p[j-1]>p[j];j--)
		{
			int t = p[j-1];
			p[j-1]=p[j];
			p[j]=t;
		}
	}
}

//After optimization
void isort2(int *p,int size)
{
	int i,j,t;
	for(i=1;i<size;i++)
	{
		t = p[i];
		for(j=i;j>0&&p[j-1]>t;j--)
		{
			p[j]=p[j-1];
		}
		p[j]=t;
	}
}

//print data
void printdata(int *p,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%d ",p[i]);
	}
}

int main(void)
{
	int i,j;
	clock_t begin,end;
	double cost;
	int array[N];
	srand((unsigned)time(NULL));
	/*
	//1 Decreasing data
	for(i=N,j=0;i>0,j<N;i--,j++)
	{
		array[j]=i;
	}
	//2 Increasing data
	for(i=0;i<N;i++)
	{
		array[i]=i;
	}
	//3 Equivalent data
	for(i=0;i<N;i++)
	{
		array[i]=8;
	}
	*/
	//4 random data
	for(i=0;i<N;i++)
	{
		array[i]=rand()%1234;
	}
	begin=clock();
	isort2(array,sizeof(array)/sizeof(int));
	end=clock();
	printdata(array,sizeof(array)/sizeof(int));
	printf("\n");
	cost=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("%5.1lf seconds\n",cost);
	return 0;
}

			
