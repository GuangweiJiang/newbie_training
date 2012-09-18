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

#define N 10000000

//Data exchange
int comp(const void *a,const void *b)
{
	return *(int*)a-*(int*)b;
}

//print data
void outsort(int *p)
{
	int i;
	for(i=0;i<N;i++)
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
	int i,j;
	int *num;
        num=(int*)malloc(N*sizeof(int));//申请内存空间
	if(num==0)return;
	srand((unsigned)time(NULL));
	for(i=0;i<N;i++)
		num[i]=rand()%45600;//生成随机数
	qsort(num,N,sizeof(int),comp);
	outsort(num);
	free(num);
	end =clock();
	cost=(double)(end-begin)/CLOCKS_PER_SEC;//计算时间
	printf("%5.1lf seconds\n",cost);
	return 0;
}
