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
	bool (*has_next)(struct st * iterator);
	void * (*next)(struct st * iterator);
	void * (*see_next)(struct st * iterator);
	void (*free_dependencies)(void * in);
	void * dependencies;
} iterator;


bool iterable_has_next(iterator * st);
void * iterable_see_next(iterator * st);
void * iterable_next(iterator * st);

iterator iterable_empty();
iterator iterable_range_long(long a, long b, long c);
iterator iterable_range_double(double a, double b, double c);
iterator iterable_iterate(int size_state,void * initial_value, bool (*hash_next)(void * element), void * (*next)(void * out, void * in));
iterator file_iterable_pchar(char * file);
iterator split_iterable_pchar(char * text, const char * delimiters);
iterator * pchar_to_iterable_pchar(iterator * out, char * in);

iterator iterable_map(iterator * st,int size_state, void * (*map_function)(void * out, const void * in));
iterator iterable_filter(iterator * st, int size_state, bool (*map_filter)(void * in));
iterator iterable_flatmap(iterator * st, int size_state, void * (*map_function)(void * out, void * in));
iterator iterable_consecutive_pairs(iterator * st, int size_element);
iterator iterable_enumerate(iterator * st);

char * iterable_tostring(iterator * st, char * (*tostring)(const void * e, char * mem), char * mem);
char * iterable_tostring_sep(iterator * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix, char * mem);
void iterable_toconsole(iterator * st, char * (*tostring)(const void * e, char * mem));
void iterable_toconsole_sep(iterator * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix);
void write_iterable_to_file(char * file, iterator * st, char * to_string(const void * source, char * mem));

iterator iterable_create(
		int size_state,
		bool (*has_next)(struct st * iterator),
		void * (*next)(struct st * iterator),
		void * (*see_next)(struct st * iterator),
		void (*free_dependencies)(void * in),
		void * dependencies,
		int size_dependencies);

void iterable_copy_state_to_auxiliary(iterator * st);

void iterable_free(iterator * in);

void test_iterables();
void test_iterables2();
void test_iterables3();

#endif /* ITERABLES_H_ */
