/*
 * user_test.c
 * longbin Li, July10'14
 *
 * Copyright (C) 2014 Wistron All rights reserved.
 *
 * This file is a user test function for link list.
 */

/* Include Files */
#include <stdio.h>
#include <string.h>
#include "linklist.h"

/* IMPLEMENTATION */
int main(){
	worker tmp = { 0 };
	worker *p_head = ll_create();
	if (p_head == NULL) {
		printf("link list create failed\n");
		return -1;
	}

	char str[10] = { 0 };
	do {
		p_head = ll_insert(p_head, ll_inputs(&tmp));
		printf("Continue inserting ? <y/n>");
		scanf("%s", str);
	} while (!strcmp(str, "y"));

	int id;
	while (p_head != NULL) {
		list_each(p_head);
		printf("Delete an element ? <y/n>");
		scanf("%s", str);
		if ((strcmp(str, "y"))) {
			break;
		}
		printf("	delete id = ");
		scanf("%d", &id);
		p_head = ll_delete(p_head, id);
	}
	list_each(p_head);

	return 0;
}
