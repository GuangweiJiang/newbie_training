/*
 * linklist.c
 * longbin Li, July10'14
 *
 * Copyright (C) 2014 Wistron All rights reserved.
 *
 * This file is a head file of linklist.c
 */

/* Include Files */
#ifndef __LINKLIST_H__
#define __LIKKLIST_H__

/* DEFINES */
typedef struct node{
	int num;
	struct node *p_next;
} node;

void ll_init();
void ll_deinit();
int ll_is_empty();
void insert_head(int);
void remove_head();
void insert_tail(int);
void remove_tail();
int get_head();
int get_tail();
int get_size();
void for_each(int (*)(void *, void *), void *);
int remove_node(int);

#endif //__LINKLIST_H__
