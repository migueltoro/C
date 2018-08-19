/*
 * list.h
 *
 *  Created on: 10 ago. 2018
 *      Author: migueltoro
 */

#ifndef LIST_H_
#define LIST_H_


#include "basic_types.h"
#include "stream.h"


typedef struct {
	type element_type;
	int size;
	int tam;
	void ** elements;
} list;

list list_empty(const type element_type);
void * list_get(const list list, const int index);
void list_add(list * list, void * element);
void list_set(list * list, int index, void * element);
list list_concat(const list ls1, const list ls2);
stream list_stream(list list);
void list_sort_naturalorder(list * ls);
void list_sort(list * ls, int (*comparator)(const void*, const void*));
void list_free(list * list);

void list_memory_clear();

extern type list_type;

#endif /* LIST_H_ */
