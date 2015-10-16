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
typedef struct worker{
	int id;
	char name[20];
	char gender[10];
	int age;
	struct worker *p_next;
} worker;

worker * ll_create(void);
worker * ll_insert(worker *head, worker *);
worker * ll_inputs(worker *);
worker * ll_delete(worker *head, int);


#endif //__LINKLIST_H__
