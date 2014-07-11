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
int print_cb(void *p_personinfo, void *p_data)
{
	if(((personinfo*)p_personinfo)->p_next){
		printf("%d ",((personinfo*)p_personinfo)->p_next->id);
		if((((personinfo*)p_personinfo)->p_next->p_next) == NULL){
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
	printf("The valid personinfo number is :%d\n", get_size());

	for_each(print_cb, NULL);
	printf("tail:%d ", get_tail());
	printf("\nremove_personinfo(1) return :%d\n", remove_personinfo(1));
	for_each(print_cb, NULL);
	printf("tail:%d\n", get_tail());

	remove_tail();
	printf("tail:%d\n", get_tail());
	remove_tail();
	printf(ll_is_empty()?"linklist is empty\n":"linklist is not empty\n");

	ll_deinit();
	return 0;
}
