/*
 * file name: ex02.c
 * pupose: Input a intger,then get how many "1" of it's binary form
 * creator: Allan xing
 * create time: 2012-09-17
 */

#include <stdio.h>
#include <stdlib.h>

int Bget(int n)
{
	int count=0;
	while(n)
	{
		n = n & (n-1);
		count++;
	}
	return count;
}

int main(void)
{
	int num;
	printf("input a intger: ");
	scanf("%d",&num);
	printf("It has %d '1'\n",Bget(num));
	return 0;

}
