/*
 * sorted_list.h
 *
 *  Created on: 1 nov. 2018
 *      Author: migueltoro
 */

#ifndef LIST_H_
#define LIST_H_

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
	memory_heap hp;
} list;

void swap_in_list(list * ls, int a, int b);

list list_empty();
list list_empty_tam(int tam);
list list_of(void * data, int size, int sizeElement);
void * list_get(list * ls, const int index);
int list_size(list * ls);
void list_add_pointer(list * ls, void * element);
void list_add(list * ls, void * element, int sizeElement);
list list_filter(list * ls, bool (*predicate)(void * e), int sizeElement);
list list_map(list * ls, void * (*f)(void * e), int sizeElement);
char * list_tostring(list * ls, char * to_string(const void * source, char * mem), char * mem);
void list_free(list * ls);
int_pair bh(list * ls, void * pivot, int i, int j, int (*order)(const void * e1, const void * e2));
void list_sort(list * ls, int (* order)(const void * e1, const void * e2));
void basic_sort(list * ls, int inf, int sup, int (*order)(const void * e1, const void * e2));
list merge_list(list * ls1, list * ls2, int (* order)(const void * e1, const void * e2));
int bs(list * ls, void * element, int (* order)(const void * e1, const void * e2));
void test_list();
#endif /* LIST_H_ */
