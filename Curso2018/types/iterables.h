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
#include "../types/preconditions.h"


typedef struct st {
	int size_state;
	int size_dependencies;
	void * state;
	void * auxiliary_state;
	bool (*has_next)(struct st * iterable);
	void * (*next)(struct st * iterable);
	void * (*see_next)(struct st * iterable);
	void (*free_dependencies)(void * in);
	void * dependencies;
} iterable;


bool iterable_has_next(iterable * st);
void * iterable_see_next(iterable * st);
void * iterable_next(iterable * st);

iterable iterable_empty();
iterable iterable_range_long(long a, long b, long c);
iterable iterable_range_double(double a, double b, double c);
iterable iterable_iterate(int size_state,void * initial_value, bool (*hash_next)(void * element), void * (*next)(void * out, void * in));
iterable file_iterable_pchar(char * file);
iterable split_iterable_pchar(char * text, const char * delimiters);
iterable * pchar_to_iterable_pchar(iterable * out, char * in);

iterable iterable_map(iterable * st,int size_state, void * (*map_function)(void * out, const void * in));
iterable iterable_filter(iterable * st, int size_state, bool (*map_filter)(void * in));
iterable iterable_flatmap(iterable * st, int size_state, void * (*map_function)(void * out, void * in));
iterable iterable_consecutive_pairs(iterable * st, int size_element);
iterable iterable_enumerate(iterable * st);

char * iterable_tostring(iterable * st, char * (*tostring)(const void * e, char * mem), char * mem);
char * iterable_tostring_sep(iterable * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix, char * mem);
void iterable_toconsole(iterable * st, char * (*tostring)(const void * e, char * mem));
void iterable_toconsole_sep(iterable * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix);
void write_iterable_to_file(char * file, iterable * st, char * to_string(const void * source, char * mem));

iterable iterable_create(
		int size_state,
		bool (*has_next)(struct st * iterable),
		void * (*next)(struct st * iterable),
		void * (*see_next)(struct st * iterable),
		void (*free_dependencies)(void * in),
		void * dependencies,
		int size_dependencies);

void iterable_copy_state_to_auxiliary(iterable * st);

void iterable_free(iterable * in);

void test_iterables();
void test_iterables2();
void test_iterables3();

#endif /* ITERABLES_H_ */
