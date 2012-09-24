/*
 * file name: ex02.c
 * purpose: Input a intger,then get how many "1" of it's binary form
 * creator: Allan xing
 * create time: 2012-09-17
 * modify time: 2012-09-20 consummate function
 * modify time: 2012-09-21 consummate error information
 * modify time: 2012-09-24 Improve function further
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int Bget1(int n)
{
	int count=0;
	while(n)
	{
		n = n & (n-1);
		count++;
	}
	return count;
}

int Bget2(int n)
{
	int m=1;
	int count=0;
	while(m)
	{
		if(n & m)
			count++;
			m <<= 1;
	}
	return count;
}

int IsNum(char *str)
{
	int i=0,num;
	int isNUM=1;
	while(str[i]!='\0'&isNUM)
	{
		if((str[i]>='0'&&str[i]<='9')||(str[0]=='-'&&str[i+1]>='0'&&str[i+1]<='9'))
		{
			i++;
		}else{
			isNUM=0;
		}
		if(isNUM)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int main(void)
{	
	char str[100];
	int count=0;
	/*
	while(str!=NULL)
	{
		printf("input a intger: ");
		scanf("%s[^\n]",str);
		if(IsNum(str))
		{
			int m=atoi(str);
			printf("It has %d '1'\n",Bget1(m));
			break;
		}
		else
		{
			printf("Input error,try again!\n");
			if(count>MAX)
			{
				printf("Sorry,illegal input exceeds the maximum limit,bye!\n");
				exit(0);
			}
			continue;
		}
		count++;
	}
	*/
	do{
		count++;
		if(count > 1 && count < MAX)
		{
			printf("Your input is not a intger! Try again:\n");
		}
		if(count>MAX)
		{
			printf("Sorry,illegal input exceeds the maximum limit,bye!\n");
			exit(0);
		}
		printf("input a intger: ");
		scanf("%s[^\n]",str);
	}while(!IsNum(str));
	int m=atoi(str);
	printf("It has %d '1'\n",Bget1(m));
	return 0;
}
