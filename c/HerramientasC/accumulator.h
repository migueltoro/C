/*
 * accumulator.h
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */

#ifndef ACCUMULATOR_H_
#define ACCUMULATOR_H_

#include "basic_types.h"
#include "new_math.h"
#include "stream.h"

typedef struct {
	type element_type;
	type base_type;
	type result_type;
	void * base_state;
	void * (* initial_value)(void * base);
	void * (*add)(void * base, void * value);
	void * (*result)(void * result_value, void * base);
	int (*isdone)(void * base);
} accumulator;



void * accumulate_left(stream * st, accumulator * ac);
void * accumulate_right(stream * st, accumulator * ac);

accumulator accumulator_sum_long();

#endif /* ACCUMULATOR_H_ */
