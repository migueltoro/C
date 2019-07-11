/*
 * accumulators.h
 *
 *  Created on: 7 jul. 2019
 *      Author: migueltoro
 */

#ifndef ACCUMULATORS_H_
#define ACCUMULATORS_H_

#include "../types/hash_table.h"
#include "../types/iterables.h"
#include "../types/list.h"
#include "../types/set.h"
#include "../types/types.h"

typedef struct {
	int size_state;
	int size_result;
	void * state;
	void * result_value;
	void * (*add)(void * base, const void * value, void * dependencies);
	void * (*result)(void * rs, const void * base, void * dependencies);
	bool (*isdone)(const void * base, void * dependencies);
	void * dependencies;
} accumulator;

accumulator create_accumulator(
		int size_state,
		int size_result,
		void * initial_value,
		void * (*add)(void * base, const void * value, void * dependencies),
		void * (*result)(void * rs, const void * base, void * dependencies),
		bool (*isdone)(const void * base, void * dependencies),
		int size_dependencies);

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

accumulator accumulator_estadisticos();
char * estadisticos_tostring(void * in, char * mem);

void * accumulate_left(iterable * st, accumulator * ac);
void * accumulate_right(iterable * st, accumulator * ac);
void * reduce_left(iterable * st, void * (*f)(void * out, const void * in));
void * reduce_right(iterable * st, void * (*f)(void * out, const void * in));
void * reduce_left_e(iterable * st, void * (*f)(void * out, const void * in),
		bool (*isdone)(const void * in));
void * reduce_right_e(iterable * st, void * (*f)(void * out, const void * in),
		bool (*isdone)(const void * in));

void * iterable_min(iterable * st,int (*comparator)(const void * e1, const void * e2));
void * iterable_max(iterable * st, int (*comparator)(const void * e1, const void * e2));
bool iterable_all(iterable * st, bool (*p)(const void * in));
bool iterable_any(iterable * st, bool (*p)(const void * in));
void * iterable_first(iterable * st, bool (*p)(const void * in));

list iterable_to_list(iterable * st, type type_element);
set iterable_to_set(iterable * st, type type_element);
hash_table iterable_counting(iterable * st, void * (*f_key)(void * out, void * in), type key_type);
hash_table iterable_grouping(iterable * st, void * (*f_key)(void * out, void * in), type key_type, type element);


void test_accumulators();
#endif /* ACCUMULATORS_H_ */
