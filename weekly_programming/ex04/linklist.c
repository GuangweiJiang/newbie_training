/*
 * linklist.c
 * longbin Li, July10'14
 *
 * Copyright (C) 2014 Wistron All rights reserved.
 *
 * This file is a linklist implement functions source file.
 */

/* Include Files */
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

/* CONSTANTS AND VARIABLES */
static node head;

/* INTERNAL FUNCTIONS */
/* initialize functon */
void ll_init()
{
	head.p_next = NULL;
}

/* destroy function */
void ll_deinit()
{/* delete the first node */
	while(head.p_next){
		node *p_tmp = head.p_next;
		head.p_next = p_tmp->p_next;
		free(p_tmp);
		p_tmp = NULL;
	}
}

/* test if the linklist if empty */
int ll_is_empty()
{
	return !(head.p_next);
}
/* insert one node */
void insert(int num)
{
	node *p_tmp = (node*)malloc(sizeof(node));
	if(p_tmp){
		p_tmp->num = num;
		p_tmp->p_next = head.p_next;
		head.p_next = p_tmp;
		printf("insert number: %d\n", num);
	}
}
/* remove the head node of the linklist */
void remove_head()
{
	if(head.p_next){
		node *p_tmp = head.p_next;
		head.p_next = p_tmp->p_next;
		free(p_tmp);
		p_tmp = NULL;
	}
}
/* insert one node to the tail of the linklist */
void insert_tail(int num)
{
	node *p_tmp = (node*)malloc(sizeof(node)), *p_node = NULL;
	if(p_tmp){
		p_tmp->num = num;
		p_tmp->p_next = NULL;
		for(p_node = &head; p_node; p_node = p_node->p_next){
			if(!(p_node->p_next)){
				p_node->p_next = p_tmp;
				break;
			}
		}
		printf("insert number: %d\n", num);
	}
}
/* delete the tail node */
void remove_tail()
{
	node *p_node = NULL;
	for(p_node = &head; p_node; p_node = p_node->p_next){
		if(p_node->p_next && !(p_node->p_next->p_next)){
			free(p_node->p_next);
			p_node->p_next = NULL;
		}
	}
}
/* get the first node */
int get_head()
{
	int ret = 1 << 31;
	if(head.p_next){
		ret = head.p_next->num; 
	}
	return ret;
}
/* get the tail node */
int get_tail()
{
	int ret = 1 << 31;
	node *p_node = NULL;
	for(p_node = &head; p_node; p_node = p_node->p_next){
		if(p_node->p_next && !(p_node->p_next->p_next)){
			ret = p_node->p_next->num;
			break;
		}
	}
	return ret;
}
/* get the number of node */
int get_size()
{
	int cnt = 0;
	node *p_node = NULL;
	for(p_node = &head; p_node; p_node = p_node->p_next){
		if(p_node->p_next){
			cnt++;
		}
	}
	return cnt;
}

/* for each function */
void for_each(int (*p_func)(void *, void *), void *p_data){
	node *p_node = NULL;
	for(p_node = &head; p_node; p_node = p_node->p_next){
		if(p_func(p_node, p_data)){
			break;
		}
	}
}

/* delete the specified node call back function */
typedef struct rdata{
	int num, ret;
}rdata;

int remove_cb(void *p_node, void *p_data)
{
	if(((node *)p_node)->p_next && (((node *)p_node)->p_next)->num == ((rdata *)p_data)->num){
		node *p_tmp = ((node *)p_node)->p_next;
		((node *)p_node)->p_next = ((node *)p_node)->p_next->p_next;
		free(p_tmp);
		p_tmp = NULL;
		((rdata *)p_data)->ret = 1;
		return 1;
	}
	return 0;
}
int remove_node(int num)
{
	rdata rd = {};
	rd.num = num;
	for_each(remove_cb , &rd);
	return rd.ret;
}

