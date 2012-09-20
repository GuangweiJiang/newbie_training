/*
 * file name: ex02.c
 * purpose: Input a intger,then get how many "1" of it's binary form
 * creator: Allan xing
 * create time: 2012-09-17
 * modify time: 2012-09-20 10:10
 * modify time: 2012-09-20 15:43
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

int IsNum(char *str)
{
	int i=0,num;
	int isNUM=1;
	while(str[i]!='\0'&isNUM)
		if((str[i]>='0'&&str[i]<='9')||(str[0]=='-'&&str[i+1]>='0'&&str[i+1]<='9'))
		{
			i++;
		}else{
			isNUM=0;
		}
	if(isNUM)
	{
		int m=atoi(str);//Convert a string to an integer
		return m;
	}else{
		printf("input error!\n");
		exit(0);
	}	

}

int main(void)
{	
	char str[100];
	printf("input a intger: ");
	scanf("%s[^\n]",str);
	printf("It has %d '1'\n",Bget(IsNum(str)));
	return 0;
}
