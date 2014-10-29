//==========================================
// Filename:
//      ex01.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      This file will sort numbers in order of size (small to large)
//
// Author/Created Date:
//      Jerry Liu, Jul.16th 2013
//==========================================
//
// 
//
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <stdio.h>
//
//
//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------
#define MAX 10000000
#define SHIFT 5           
#define MASK 0x1F
#define DIGITS 32
//
//
int a[1+MAX/DIGITS];
//-----------------------------------------------------------------
// SET FUNCTIONS :The function is 
//-----------------------------------------------------------------
void set(int n)     //将逻辑位置为n的二进制位置为1 
{
	a[n>>SHIFT]=a[n>>SHIFT]|(1<<(n&MASK));      //n>>SHIFT右移5位相当于除以32求算字节位置，n&MASK相当于对32取余即求位位置，
}                                              	//然后将1左移的结果与当前数组元素进行或操作，相当于将逻辑位置为n的二进制位置1.  

void clear(int n)
{
	a[n>>SHIFT]=a[n>>SHIFT]&(~(1<<(n&MASK)));   //将逻辑位置为n的二进制位置0，原理同set操作 
}

int test(int n)
{
	return a[n>>SHIFT] & (1<<(n&MASK));         //测试逻辑位置为n的二进制位是否为1 
}

int main(int argc, char *argv[])
{
	int i,n;
	for(i=1;i<=MAX;i++)
	{
		clear(i);
	}    
		while(scanf("%d",&n)!=EOF)
		{
			set(n);
		}
	for(i=1;i<=MAX;i++)
	{
			if(test(i))
			printf("%d ",i);
	}
	return 0;
}
