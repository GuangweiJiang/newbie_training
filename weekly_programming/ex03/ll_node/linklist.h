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
struct worker{
	int id;
	char name[20];
	char gender[12];
	int age;
};
typedef struct ll_node{
	struct worker worker;
	struct ll_node *p_next;
} ll_node, *link_list;

link_list ll_create(void);
link_list ll_locate(link_list head, int);
int ll_inputs(ll_node *);
int ll_insert(link_list head, ll_node *);
int ll_delete(link_list head, int);


#endif //__LINKLIST_H__
