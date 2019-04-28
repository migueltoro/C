/*
 * sorted_list.h
 *
 *  Created on: 1 nov. 2018
 *      Author: migueltoro
 */

#ifndef ALIST_H_
#define ALIST_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "math2.h"
#include "types.h"
#include "memory_heap.h"

typedef struct {
	int size;
	int tam;
	void ** elements;
} alist;

void swap_in_list(alist * ls, int a, int b);

alist alist_empty();
alist alist_empty_tam(int tam);
alist alist_of(void * data, int size, int sizeElement);
void * alist_get(alist * ls, const int index);
int alist_size(alist * ls);
void alist_add(alist * ls, void * element);
void alist_add_m(alist * ls, void * element,int sizeElement, memory_heap * hp);
alist alist_filter(alist * ls, bool (*predicate)(void * e));
alist alist_map(alist * ls, void * (*f)(void * e));
char * alist_tostring(alist * ls, char * to_string(const void * source, char * mem), char * mem);
void alist_free(alist * ls);
int_pair bh(alist * ls, void * pivot, int i, int j, int (*order)(const void * e1, const void * e2));
void alist_sort(alist * ls, int (* order)(const void * e1, const void * e2));
void basic_sort(alist * ls, int inf, int sup, int (*order)(const void * e1, const void * e2));
alist merge_list(alist * ls1, alist * ls2, int (* order)(const void * e1, const void * e2));
int bs(alist * ls, void * element, int (* order)(const void * e1, const void * e2));
void test_list();
#endif /* ALIST_H_ */
