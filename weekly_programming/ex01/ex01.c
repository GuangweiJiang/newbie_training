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

#define N 10000

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
void outsort(int *p)
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("%d ",p[i]);
	}
	printf("\n");
}
void mopop(int p[])
{
	int i,j,flag;
	for(i=0;i<N-1;i++){
		flag=1;
		for(j=0;j<N-i-1;j++){
			if(p[j]>p[j+1]){
				swap(&p[j],&p[j+1]);
				flag=0;
			}
		}
		if(1==flag)break;
	}
}

int main(void)
{
	clock_t begin,end;
	double cost;
	time_t t;
//	int array[10]={9,8,7,6,5,4,3,2,1,0};
//	quicksort(array,0,sizeof(array)/sizeof(int)-1);
//	outsort(array);
	begin=clock();
	int i,j;
	int *num=0;
	num=(int*)malloc(10*sizeof(int));//申请内存空间
	if(num==0)return;
	srand((unsigned)time(&t));
	for(i=0;i<N;i++)
		num[i]=rand()%456;//生成随机数
	//	printf("%d ",p[i]);
//	outsort(num);
	mopop(num);	
//	quicksort(num,0,sizeof(num)/sizeof(int)-1);
	outsort(num);
	free(num);
	end =clock();
	cost=(double)(end-begin)/CLOCKS_PER_SEC;//计算时间
	printf("%5.1lf seconds\n",cost);
	return 0;
}
