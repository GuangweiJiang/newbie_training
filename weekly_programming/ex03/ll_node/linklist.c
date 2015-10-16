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
int ll_inputs(ll_node *tmp)
{
	if (tmp == NULL) {
		return -1;
	}
	printf("please type your id :");
	scanf("%d", &tmp->worker.id);
	printf("please type your name :");
	scanf("%s", tmp->worker.name);
	printf("please type your gender :");
	scanf("%s", tmp->worker.gender);
	printf("please type your age :");
	scanf("%d", &tmp->worker.age);

	return 1;
}

/* link list create function */
link_list ll_create(void)
{
	printf("start to create a new link list.\n");
	link_list l_head = (ll_node *)malloc(sizeof(struct ll_node));
	if (l_head == NULL) {
		printf("malloc failed!\n");
		return NULL;
	}
	l_head->p_next = NULL;
	ll_node  *this = NULL, *new;
	this = l_head;
	char buf[10] = { 0 };
	do {
		new = (ll_node *)malloc(sizeof(struct ll_node));
		if (new == NULL) {
			printf("malloc error\n");
			return NULL;
		}
		this->p_next = new;
		ll_inputs(new);
		this = new;
		printf("Continue to input data? <y/n>");
		scanf("%s", buf);
	} while (!strcmp(buf, "y"));
	if (l_head->p_next != NULL){ /* link list is not NULL */
		this->p_next = NULL;
	}

	printf("list link create over\n");
	return l_head;
}

/* locate link list funciton */
ll_node * ll_locate(link_list head, int id)
{
	ll_node *tmp = head->p_next;
	while (tmp != NULL && tmp->worker.id != id) {
		tmp = tmp->p_next;
	}
	return tmp;
}

/* link list insert function */
int ll_insert(link_list head, ll_node *p_one)
{
	printf("start to insert a new node.\n");
	ll_node *fro, *this, *new;
	if (p_one == NULL) {
		return -1;
	}

	new = (ll_node *)malloc(sizeof(struct ll_node));
	if (new == NULL) {
		printf("malloc error\n");
		return -1;
	}
		new->worker.id = p_one->worker.id;
		strcpy(new->worker.name, p_one->worker.name);
		strcpy(new->worker.gender, p_one->worker.gender);
		new->worker.age = p_one->worker.age;
		new->p_next = NULL;
	this = head;
	while (this != NULL) {
		fro = this;
		this = this->p_next;
		if (this != NULL && this->worker.id >= new->worker.id) {
			new->p_next = this;
			fro->p_next = new;
			break;
		}
	}
	if (this == NULL) {
		fro->p_next = new;
	}
	printf("list link insert over\n");
	return 1;
}

/* link list delete function */
int ll_delete(ll_node *head, int id)
{
	if (head->p_next == NULL) {
		printf("data invalid\n");
		return -1;
	}
	ll_node *fro, *this;
	this = head->p_next;
	if (this->worker.id == id && this->p_next == NULL) {
		printf("delete the last data\n");
		free(this);
		this = NULL;
		head->p_next = NULL;
		return 1;
	}
	for (this = head; this;) {
		fro = this;
		this = this->p_next;
		if (this != NULL && this->worker.id == id) {
			printf("delete id %d\n", id);
			fro->p_next = this->p_next;
			free(this);
			this = NULL;
			break;
		}
	}
	if (this == NULL) {
		printf("%d not exists, do nothing\n", id);
	}
	return 1;
}

/* link list for each list */
void list_each(ll_node *head)
{
	ll_node *this;
	if (head->p_next == NULL) {
		printf("------list for each:\t");
		printf("no data!\n");
	} else {
		this = head->p_next;
		do {
			printf("------list for each:\t");
			printf("id=%d,\tname=%s,\tgender=%s,\tage=%d\n",this->worker.id, this->worker.name, this->worker.gender, this->worker.age);
			this = this->p_next;
		} while (this != NULL);
	}
}
