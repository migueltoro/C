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
list list_of_pchar(char ** data, int size);
list list_of_string_of_file(char * file);

list list_sublist(list * ls, int a, int b);
void * list_get(list * ls, const int index);
char * list_get_string(list * ls, const int index, char * mem);
int list_size(list * ls);
void list_add_pointer(list * ls, void * element);
void list_add(list * ls, void * element);
void list_add_left(list * ls, void * element);
void * list_set(list * list, const int index, const void * e);
void list_set_pointer(list * list, int index, void * element);

list list_filter(list * ls, bool (*predicate)(void * e), int size_element);
list list_map(list * ls, void * (*f)(void * out, void * in), type type_element);

char * list_tostring(list * ls, char * mem);
bool list_contains(list * list, const void * e);
bool list_equals(const list * ls1, const list * ls2);
list * list_parse(list * out, char * text);
list list_parse_s(char * text);

void write_list_to_file(char * file, list * list, char * tostring(const void * source, char * mem));

iterator list_iterable(list * ls);

extern type list_type;

int_pair bh(list * ls, void * pivot, int i, int j, int (*order)(const void * e1, const void * e2));
void list_sort(list * ls, int (* order)(const void * e1, const void * e2));
void basic_sort(list * ls, int (*order)(const void * e1, const void * e2));
list merge_list(list * ls1, list * ls2, int (* order)(const void * e1, const void * e2));
int bs(list * ls, void * element, int (* order)(const void * e1, const void * e2));

void list_free(list * ls);
void list_free_2(list * ls, void (*f)(void * in));
void test_list();
#endif /* LIST_H_ */
