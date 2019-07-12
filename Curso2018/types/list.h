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

#include "../types/iterables.h"
#include "../types/math2.h"
#include "../types/memory_heap.h"
#include "../types/types.h"

typedef struct {
	bool is_view;
	type type_element;
	int size;
	int tam;
	void ** elements;
	memory_heap hp;
} list;

void swap_in_list(list * ls, int a, int b);

list list_empty(type element);
list list_empty_tam(type element, int tam);
list list_of(void * data, int size, type type_element);
list list_sublist(list * ls, int a, int b);
void * list_get(list * ls, const int index);
int list_size(list * ls);
void list_add_pointer(list * ls, void * element);
void list_add(list * ls, void * element);

list list_filter(list * ls, bool (*predicate)(void * e), int sizeElement);
list list_map(list * ls, void * (*f)(void * e), type type_element);
char * list_tostring(list * ls, char * mem);

void write_list_to_file(char * file, list * list, char * to_string(const void * source, char * mem));
list lines(char * file);

iterable list_iterable(list * ls);



int_pair bh(list * ls, void * pivot, int i, int j, int (*order)(const void * e1, const void * e2));
void list_sort(list * ls, int (* order)(const void * e1, const void * e2));
void basic_sort(list * ls, int (*order)(const void * e1, const void * e2));
list merge_list(list * ls1, list * ls2, int (* order)(const void * e1, const void * e2));
int bs(list * ls, void * element, int (* order)(const void * e1, const void * e2));

void list_free(list * ls);
void test_list();
#endif /* LIST_H_ */
