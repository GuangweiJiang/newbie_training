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
#include <string.h>
#include "linklist.h"

/* INTERNAL FUNCTIONS */

/* link list gets element function */
worker * ll_inputs(worker *tmp)
{
	if (tmp == NULL) {
		return NULL;
	}
	printf("please type your id :");
	scanf("%d", &tmp->id);
	printf("please type your name :");
	scanf("%s", tmp->name);
	printf("please type your gender :");
	scanf("%s", tmp->gender);
	printf("please type your age :");
	scanf("%d", &tmp->age);

	return tmp;
}

/* link list create function */
worker * ll_create(void)
{
	printf("start to create a new link list.\n");
	worker *head, *this, *new;
	new = (worker *)malloc(sizeof(struct worker));
	ll_inputs(new);
	if (new == NULL) {
		printf("malloc error\n");
		return NULL;
	}
	head = new;
	new->p_next = NULL;
	printf("list link create over\n");
	return head;
}

/* link list insert function */
worker * ll_insert(worker *head, worker *p_one)
{
	printf("start to insert a new node.\n");
	worker *new, *this, *fro;
	if (p_one == NULL) {
		return NULL;
	}

	new = (worker *)malloc(sizeof(struct worker));
	if (new == NULL) {
		printf("malloc error\n");
		return NULL;
	}
		new->id = p_one->id;
		strcpy(new->name, p_one->name);
		strcpy(new->gender, p_one->gender);
		new->age = p_one->age;
		new->p_next = NULL;
	if (head == NULL) {
		head = new;
	} else {
		this = head;
		while (this != NULL && this->id <= p_one->id) {
			if (this->id == p_one->id) {
				printf("this id already exists\n");
				free(new);
				new = NULL;
				return head;
			}
			fro = this;
			this = this->p_next;
		}
		if (this == head) {
			new->p_next = this;
			head = new;
		} else {
			fro->p_next = new;
			new->p_next = this;
		}
	}
	printf("list link insert over\n");
	return head;
}

/* link list delete function */
worker * ll_delete(worker *head, int id)
{
	if (head == NULL) {
		printf("data invalid\n");
		return NULL;
	}
	worker *this, *fro;
	this = head;
	if (this->id == id && this->p_next == NULL) {
		printf("delete the last data\n");
		free(head);
		head = NULL;
		return head;
	}
	while (this != NULL && this->id != id) {
		fro = this;
		this = this->p_next;
	}
	if (this != NULL) {
		if (this == head) {
			head = head->p_next;
		} else {
			fro->p_next = this->p_next;
		}
		free(this);
		this = NULL;
		printf("delete ok\n");
	} else {
		printf("%d not exists, do nothing\n", id);
	}
	return head;
}

/* link list for each list */
void list_each(worker *head)
{
	worker *this;
	if (head == NULL) {
		printf("------list for each:\t");
		printf("no data!\n");
	} else {
		this = head;
		do {
			printf("------list for each:\t");
			printf("id=%d,\tname=%s,\tgender=%s,\tage=%d\n",this->id, this->name, this->gender, this->age);
			this = this->p_next;
		} while (this != NULL);
	}
}
