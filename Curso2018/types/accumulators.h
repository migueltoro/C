/*
 * accumulators.h
 *
 *  Created on: 7 jul. 2019
 *      Author: migueltoro
 */

#ifndef ACCUMULATORS_H_
#define ACCUMULATORS_H_

#include "../types/types.h"
#include "../types/hash_table.h"
#include "../types/iterables.h"
#include "../types/list.h"
#include "../types/set.h"
#include "../types/multiset.h"




typedef struct {
	int num;
	double sum;
	double sum_cuadrados;
	double max;
	double min;
	double media;
	double varianza;
	double desviacion_tipica;
} estadisticos;

char * estadisticos_tostring(void * in, char * mem);

void * accumulate_left(iterator * st, void * base,
		void * (*add)(void * out, const void * e));
void * accumulate_left_e(iterator * st, void * base,
		void * (*add)(void * out, const void * e),
		bool isdone(void *));
void * accumulate_left_e_r(iterator * st, void * base,
		void * result,
		void * (*add)(void * out, const void * e),
		bool isdone(void * in), void * (*f_result)(void * out, const void * in));

void * accumulate_right(iterator * st, void * base, int size_element,
		void * (*add)(void * out, const void * e));
void * accumulate_right_r(iterator * st, void * base, void * result, int size_element,
		void * (*add)(void * out, const void * e),
		void * (f_result)(void * out, const void * e));

void * reduce_left(iterator * st, void * base, int size_base,
		void * (*add)(void * out, const void * e));
void * reduce_left_e(iterator * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *));
void * reduce_right(iterator * st, void * base, int size_base,
		void * (*add)(void * out, const void * e));
void * reduce_right_e(iterator * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *));


void * iterable_min(iterator * st,int (*comparator)(const void * e1, const void * e2));
void * iterable_max(iterator * st, int (*comparator)(const void * e1, const void * e2));
bool iterable_all(iterator * st, bool (*p)(const void * in));
bool iterable_any(iterator * st, bool (*p)(const void * in));
void * iterable_first(iterator * st, bool (*p)(const void * in));
double iterable_sum(iterator * st);
int iterable_size(iterator * st);
double iterable_average(iterator * st);


list iterable_to_list(iterator * st, type type_element);
set iterable_to_set(iterator * st, type type_element);
multiset iterable_to_multiset(iterator * st, type type_element);
hash_table iterable_counting(iterator * st, void * (*f_key)(void * out, void * in), type key_type);
hash_table iterable_grouping(iterator * st, void * (*f_key)(void * out, void * in), type key_type, type element);



void test_accumulators();
void test_accumulators2();
#endif /* ACCUMULATORS_H_ */
