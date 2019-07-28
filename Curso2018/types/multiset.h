/*
 * multiset.h
 *
 *  Created on: 25 jul. 2019
 *      Author: migueltoro
 */

#ifndef MULTISET_H_
#define MULTISET_H_

#include "../types/hash_table.h"
#include "../types/iterables.h"
#include "../types/list.h"
#include "../types/types.h"

typedef struct {
	hash_table hash_table;
	memory_heap hp;
	type type_element;
} multiset;

multiset multiset_empty(type type_element);
multiset multiset_of(list * ls);
void multiset_add_pointer(multiset * st, void * element, int n);
void multiset_add(multiset * st, void * element, int n);
void multiset_remove(multiset * st, void * element, int n);
int multiset_size(multiset * st);
bool multiset_contains(multiset * st, void * element);
int multiset_count(multiset * st, void * element);

char * multiset_tostring(multiset * st, char * mem);

iterator multiset_iterable(multiset * st);

void multiset_free(multiset * st);
void multiset_free_2(multiset * st, void (*f)(void * in));

multiset complete_multiset();
void test_multiset();

#endif /* MULTISET_H_ */
