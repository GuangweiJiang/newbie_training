//==========================================
// Filename:
//      ex02.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      This file will count the numbers of "1" in the binary numbers.
//
// Author/Created Date:
//      Jerry Liu Jul.5 2013
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <stdio.h>
//
//
//--------------------------------------------------------------------------------------
// MAIN FUNCTION
//--------------------------------------------------------------------------------------
void main()
{
	int n,j;
	scanf("%d",&n);
	j=cz (n);
	printf("The number is %d\n",j);
}
//
//
//--------------------------------------------------------------------------------------
// CHAOZHAO FUNCTION
//--------------------------------------------------------------------------------------
int cz(int i)
{
	int count = 0;
	unsigned int flag = 1;
	while(flag)
	{
	if(i & flag)
		count ++;
		flag = flag << 1;
	 }
	return count;
}
//----------------------------------------------------------------------------
// Function:
// 			int cz(int i)
//
// Description:
//			The function is used to count the numbers of "1" in the binary numbers.
