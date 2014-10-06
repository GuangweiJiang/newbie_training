/*
 * sort.c
 * longbin Li, July10'14
 *
 * Copyright (C) 2014 Wistron All rights reserved.
 *
 * This file is a user test function for link list.
 */

/* Include Files */
#include "sort.h"

/* IMPLEMENTATION */

/* generate an array */
void generate(int* arr, int size){
	srand(time(0));
	int i = 0;
	for (i = 0; i <= size - 1; i++) {
		arr[i] = rand() % 10000;
	}
	printf("data generated ok !\n");
}

/* display the elements of an array */
void show_array(int *arr, int size){
	int i = 0;
	for (i = 0; i <= size - 1; i++) {
		printf("%d\t", arr[i]);
	}
	printf("print over !\n");
}

/* show time */
void show_time(){
	time_t now = time(NULL);
	struct tm *mytm = localtime(&now);
	printf("%04d-%02d-%02d %02d:%02d:%02d now=%d\n",
			mytm->tm_year+1900, mytm->tm_mon+1, mytm->tm_mday,
			mytm->tm_hour, mytm->tm_min, mytm->tm_sec, (int)now);
}

/* sorting functions */
/* bubble sorting function */
void bubble_sort(int *arr, int size){
	int outer = 0, inner = 0;
	for (outer = 0; outer < size - 1; outer++) {
		for (inner = 0; inner < size - outer; inner++) {
			if (arr[inner] > arr[inner+1]) {
				arr[inner] ^= arr[inner+1];
				arr[inner+1] ^= arr[inner];
				arr[inner] ^= arr[inner+1];
			}
		}
	}
	printf("bubble sort over !\n");
}

/* insert sorting function */
void insert_sort(int *arr, int size){
	int outer = 0, inner = 0;
	int tmp = 0;
	for (outer = 1; outer < size; outer++) {
		for (inner = outer; inner > 0 && arr[inner-1] > arr[inner]; inner--) {
			/* swap two elements */
			tmp = arr[inner];
			arr[inner] = arr[inner-1];
			arr[inner-1] = tmp;
		}
	}
	printf("insert sorting sorted over !\n");
}
/* insert sorting improved function */
void insert_sort_improved(int *arr, int size){
	int outer = 0, inner = 0;
	int tmp;
	for (outer = 1; outer < size; outer++) {
		tmp = arr[outer];
		for (inner = outer; inner > 0 && arr[inner-1] > arr[inner]; inner--) {
			arr[inner] = arr[inner-1];
		}
		arr[inner] = tmp;
	}

	printf("insert sorting improved sorted over !\n");
}

/* select sorting function */
void select_sort(int *arr, int size){
	int pos = 0, inner = 0;
	int tmp;
	for (pos = 0; pos < size; pos++) {
		for (inner = pos + 1; inner < size; inner++) {
			if (arr[pos] > arr[inner]) {
				/* swap two elements */
				tmp = arr[pos];
				arr[pos] = arr[inner];
				arr[inner] = tmp;
			}
		}
	}
	printf("select sorting sorted over !\n");
}

/* quick sorting function */
void quick_sort(int *arr, int size){
	

	printf("qucik sorting sorted over !\n");
}

/* merge sorting function */
void merge_sort(int *arr, int size){
	
	printf("merge sorting sorted over !\n");
}
