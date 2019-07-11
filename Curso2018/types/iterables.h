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
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#include "../types/math2.h"
#include "../types/memory_heap.h"
#include "../types/types.h"


typedef struct st {
	memory_heap hp;
	int size_state;
	void * state;
	void * auxiliary_state;
	bool (*has_next)(struct st * iterable);
	void * (*next)(struct st * iterable);
	void * (*see_next)(struct st * iterable);
	void * dependencies;
} iterable;

bool iterable_has_next(iterable * st);
void * iterable_see_next(iterable * st);
void * iterable_next(iterable * st);

iterable iterable_range_long(long a, long b, long c);
iterable iterable_range_double(double a, double b, double c);
iterable iterable_iterate(int size_state,void * initial_value, bool (*hash_next)(void * element), void * (*next)(void * out, void * in));
iterable file_iterable(char * file);
iterable split_iterable(char * text, const char * delimiters);

iterable iterable_map(iterable * st, int size_state, void * (*map_function)(void * out, void * in));
iterable iterable_filter(iterable * st, int size_state, bool (*map_filter)(void * in));

char * iterable_tostring(iterable * st, char * (*tostring)(const void * e, char * mem), char * mem);
char * iterable_tostring_sep(iterable * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix, char * mem);
void iterable_toconsole(iterable * st, char * (*tostring)(const void * e, char * mem));
void iterable_toconsole_sep(iterable * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix);
void write_iterable_to_file(char * file, iterable * st, char * to_string(const void * source, char * mem));

iterable create_iterable(
		int size_state,
		bool (*has_next)(struct st * iterable),
		void * (*next)(struct st * iterable),
		void * (*see_next)(struct st * iterable),
		void * dependencies,
		int size_dependencies);
void copy_state_to_auxiliary(iterable * st);

void test_iterables();

#endif /* ITERABLES_H_ */
