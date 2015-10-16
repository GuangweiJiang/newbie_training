/*
 * Filename:				bit_cnt.c
 *
 * Copyright (C) 2014 Wistron
 * All rights reserved.
 *
 * Description:				This file is a sort function.
 * Author/Created Date:		longbin Li, July2'14
 * Modification History:
 * Note:
 */

/* Include Files */
#include <stdio.h>

/* MACROS */
#define	NUM		10

/* INTERNAL FUNCTIONS */

int bit_cnt(int n)
{
	int i, count = 0;
	for (i = 0; i <= 31; i++) {
		count += (n >> i) & 1;
	}
	return count;
}

/* IMPLEMENTATION */
int main()
{
	int res, n = NUM;
	res = bit_cnt(n);
	printf("The num %d has %d bit(s) 1. \n", n, res);
	return 0;
}

