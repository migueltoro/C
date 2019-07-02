/*
 * iterables.h
 *
 *  Created on: 1 jul. 2019
 *      Author: migueltoro
 */



#ifndef ITERABLES_H_
#define ITERABLES_H_

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
#include "list.h"
#include "hash_table.h"
#include "set.h"


typedef struct st {
	memory_heap hp;
	int size_state;
	void * state;
	void * auxiliary_state;
	bool (*has_next)(struct st * iterable, void * dependencies);
	void * (*next)(struct st * iterable, void * dependencies);
	void * (*see_next)(struct st * iterable, void * dependencies);
	void * dependencies;
} iterable;

iterable iterable_map(iterable * st, int size_state, void * (*map_function)(void * out, void * in));
iterable iterable_filter(iterable * st, int size_state, bool (*map_filter)(void * in));

iterable iterable_range_long(long a, long b, long c);
iterable iterable_iterate(int size_state,void * initial_value, bool (*hash_next)(void * element),void * (*next)(void * state));


iterable file_iterable(char * file);
iterable list_iterable(list * ls);

bool iterable_has_next(iterable * st);
void * iterable_see_next(iterable * st);
void * iterable_next(iterable * st);

list iterable_to_list(iterable * st, int size_element);
set iterable_to_set(iterable * st, int size_element,
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e, char * mem));
hash_table counting(iterable * st,
		void * (*f_key)(void * e),
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e, char * mem));
hash_table grouping(iterable * st,
		void * (*f_key)(void * e),
		int (*equals_key)(const void *, const void *),
		char * (*tostring_key)(const void * e, char * mem));

void test_iterables();

#endif /* ITERABLES_H_ */
