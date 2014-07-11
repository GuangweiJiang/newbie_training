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
static personinfo head;

/* INTERNAL FUNCTIONS */
/* initialize functon */
void ll_init()
{
	head.p_next = NULL;
}

/* destroy function */
void ll_deinit()
{/* delete the first personinfo */
	while(head.p_next){
		personinfo *p_tmp = head.p_next;
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
/* insert one personinfo */
void insert(int id)
{
	personinfo *p_tmp = (personinfo*)malloc(sizeof(personinfo));
	if(p_tmp){
		p_tmp->id = id;
		p_tmp->p_next = head.p_next;
		head.p_next = p_tmp;
		printf("insert number: %d\n", id);
	}
}
/* remove the head personinfo of the linklist */
void remove_head()
{
	if(head.p_next){
		personinfo *p_tmp = head.p_next;
		head.p_next = p_tmp->p_next;
		free(p_tmp);
		p_tmp = NULL;
	}
}
/* insert one personinfo to the tail of the linklist */
void insert_tail(int id)
{
	personinfo *p_tmp = (personinfo*)malloc(sizeof(personinfo)), *p_personinfo = NULL;
	if(p_tmp){
		p_tmp->id = id;
		p_tmp->p_next = NULL;
		for(p_personinfo = &head; p_personinfo; p_personinfo = p_personinfo->p_next){
			if(!(p_personinfo->p_next)){
				p_personinfo->p_next = p_tmp;
				break;
			}
		}
		printf("insert number: %d\n", id);
	}
}
/* delete the tail personinfo */
void remove_tail()
{
	personinfo *p_personinfo = NULL;
	for(p_personinfo = &head; p_personinfo; p_personinfo = p_personinfo->p_next){
		if(p_personinfo->p_next && !(p_personinfo->p_next->p_next)){
			free(p_personinfo->p_next);
			p_personinfo->p_next = NULL;
		}
	}
}
/* get the first personinfo */
int get_head()
{
	int ret = 1 << 31;
	if(head.p_next){
		ret = head.p_next->id; 
	}
	return ret;
}
/* get the tail personinfo */
int get_tail()
{
	int ret = 1 << 31;
	personinfo *p_personinfo = NULL;
	for(p_personinfo = &head; p_personinfo; p_personinfo = p_personinfo->p_next){
		if(p_personinfo->p_next && !(p_personinfo->p_next->p_next)){
			ret = p_personinfo->p_next->id;
			break;
		}
	}
	return ret;
}
/* get the idber of personinfo */
int get_size()
{
	int cnt = 0;
	personinfo *p_personinfo = NULL;
	for(p_personinfo = &head; p_personinfo; p_personinfo = p_personinfo->p_next){
		if(p_personinfo->p_next){
			cnt++;
		}
	}
	return cnt;
}

/* for each function */
void for_each(int (*p_func)(void *, void *), void *p_data){
	personinfo *p_personinfo = NULL;
	for(p_personinfo = &head; p_personinfo; p_personinfo = p_personinfo->p_next){
		if(p_func(p_personinfo, p_data)){
			break;
		}
	}
}

/* delete the specified personinfo call back function */
typedef struct rdata{
	int id, ret;
}rdata;

int remove_cb(void *p_personinfo, void *p_data)
{
	if(((personinfo *)p_personinfo)->p_next && (((personinfo *)p_personinfo)->p_next)->id == ((rdata *)p_data)->id){
		personinfo *p_tmp = ((personinfo *)p_personinfo)->p_next;
		((personinfo *)p_personinfo)->p_next = ((personinfo *)p_personinfo)->p_next->p_next;
		free(p_tmp);
		p_tmp = NULL;
		((rdata *)p_data)->ret = 1;
		return 1;
	}
	return 0;
}
int remove_personinfo(int id)
{
	rdata rd = {};
	rd.id = id;
	for_each(remove_cb , &rd);
	return rd.ret;
}

