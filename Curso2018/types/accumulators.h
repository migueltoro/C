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

char * estadisticos_tostring(void * in, char * mem);

void * accumulate_left(iterable * st, void * base,
		void * (*add)(void * out, const void * e));
void * accumulate_left_e(iterable * st, void * base,
		void * (*add)(void * out, const void * e),
		bool isdone(void *));
void * accumulate_left_e_r(iterable * st, void * base,
		void * result,
		void * (*add)(void * out, const void * e),
		bool isdone(void * in), void * (*f_result)(void * out, const void * in));



void * reduce_left(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e));
void * reduce_left_e(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *));
void * reduce_right(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e));
void * reduce_right_e(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *));


void * iterable_min(iterable * st,int (*comparator)(const void * e1, const void * e2));
void * iterable_max(iterable * st, int (*comparator)(const void * e1, const void * e2));
bool iterable_all(iterable * st, bool (*p)(const void * in));
bool iterable_any(iterable * st, bool (*p)(const void * in));
void * iterable_first(iterable * st, bool (*p)(const void * in));
double iterable_sum(iterable * st);
int iterable_size(iterable * st);
double iterable_average(iterable * st);


list iterable_to_list(iterable * st, type type_element);
set iterable_to_set(iterable * st, type type_element);
hash_table iterable_counting(iterable * st, void * (*f_key)(void * out, void * in), type key_type);
hash_table iterable_grouping(iterable * st, void * (*f_key)(void * out, void * in), type key_type, type element);


accumulator string_accumulator();

void test_accumulators();
void test_accumulators2();
#endif /* ACCUMULATORS_H_ */
