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
#include "linklist.h"

/* INTERNAL FUNCTIONS */
int print_cb(void *p_node, void *p_data)
{
	if(((node*)p_node)->p_next){
		printf("%d ",((node*)p_node)->p_next->num);
		if((((node*)p_node)->p_next->p_next) == NULL){
			printf("\n");
			return 1;
		}
	}
	return 0;
}

/* IMPLEMENTATION */
int main(){
	ll_init();

	insert_tail(1);
	insert_tail(2);
	insert_tail(3);
	printf("The valid node number is :%d\n", get_size());

	for_each(print_cb, NULL);
	printf("tail:%d ", get_tail());
	printf("\nremove_node(1) return :%d\n", remove_node(1));
	for_each(print_cb, NULL);
	printf("tail:%d\n", get_tail());

	remove_tail();
	printf("tail:%d\n", get_tail());
	remove_tail();
	printf(ll_is_empty()?"linklist is empty\n":"linklist is not empty\n");

	ll_deinit();
	return 0;
}
