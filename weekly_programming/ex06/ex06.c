/*
 * file name: ex06.c
 * purpose: use bitmap sort to sort the numbers of a file
 * create time: 2012-11-21
 * creator: Allan xing
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#define K 10000000
#define SHIFT 5
#define MASK 0x1F
#define DIGITS 32

int a[1+K/DIGITS];

void set_bit(int n)
{
	a[n>>SHIFT]=a[n>>SHIFT]|(1<<(n&MASK));
}

void clear_bit(int n)
{
	a[n>>SHIFT]=a[n>>SHIFT]&(~(1<<(n&MASK)));
}

int test_bit(int n)
{
	return a[n>>SHIFT] & (1<<(n&MASK));
}

int main(int argc,char* argv[])
{
	int i;
	int n;
	
	FILE *in;
	FILE *out;
	if((in = fopen("./file.txt","r")) == NULL)
	{
		printf("open file error!\n");
		exit(0);
	}

	if((out = fopen("./bit_sort.txt","w+")) == NULL)
	{
		printf("open file1 error!\n");
		exit(0);
	}
	printf("clear....\n");
	for(i=1;i<=K;i++)
	{
		clear_bit(i);
	}
	printf("clear over....\n");
	printf("set....\n");
	while(!feof(in))
	{
		fscanf(in,"%d",&n);
		set_bit(n);
	}
	printf("set over....\n");
	for(i=1;i<=K;i++)
	{
		if(test_bit(i))
			fprintf(out,"%5d ",i);
	}
	fclose(in);
	fclose(out);
	return 0;
}
