/*
 * file name: ex02.c
 * purpose: Input a intger,then get how many "1" of it's binary form
 * creator: Allan xing
 * create time: 2012-09-17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	char str[100];
	int i=0;
	int isNUM=1;
	printf("input a intger: ");
	scanf("%s[^\n]",str);
	while(str[i]!='\0'&isNUM)
		if(str[i]>='0'&&str[i]<='9')
		{
			i++;
		}else{
			isNUM=0;
		}
	if(isNUM)
	{
		int m=atoi(str);//Convert a string to an integer
		printf("It has %d '1'\n",Bget(m));
	}else{
		printf("input error!\n");
	return 0;
	}	
}
