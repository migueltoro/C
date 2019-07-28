/*
 * set.h
 *
 *  Created on: 28 abr. 2019
 *      Author: migueltoro
 */

#ifndef SET_H_
#define SET_H_


#include "../types/types.h"
#include "../types/hash_table.h"
#include "../types/iterables.h"
#include "../types/list.h"

typedef struct {
	hash_table hash_table;
	memory_heap hp;
	type type_element;
	iterator iterable;
} set;

set set_empty(type type_element);
set set_of(list * ls);
void set_add_pointer(set * st, void * element);
void set_add(set * st, void * element);
int set_size(set * st);
bool set_contains(set * st, void * element);

char * set_tostring(set * st, char * mem);

iterator set_iterable(set * st);

void set_free(set * st);
void set_free_2(set * st, void (*f)(void * in));

set complete_set();
void test_set();

#endif /* SET_H_ */
