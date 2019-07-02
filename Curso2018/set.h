/*
 * set.h
 *
 *  Created on: 28 abr. 2019
 *      Author: migueltoro
 */

#ifndef SET_H_
#define SET_H_

#include "hash_table.h"
#include "types.h"

typedef struct {
	hash_table hash_table;
	memory_heap hp;
} set;

set set_empty(
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem));
set set_of(list * ls,
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem));
void set_add_pointer(set * st, void * element);
void set_add(set * st, void * element, int sizeElement);
int set_size(set * st);
bool set_contains(set * st, void * element);
char * set_tostring(set * st, char * to_string(const void * source, char * mem), char * mem);
void set_free(set * st);
void test_set();

#endif /* SET_H_ */
