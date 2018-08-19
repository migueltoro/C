/*
 * accumulator.c
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */

#include "accumulator.h"
#include "stream.h"

//typedef struct {
//	type element_type;
//	type base_type;
//	type result_type;
//	void * base_state;
//	void * (* initial_value)();
//	void * (*add)(void * base, void * value);
//	void * (*result)(void * result_value, void * base);
//	int (*isdone)(void * base);
//} accumulator;

int is_done_false(void * base){
	return 0;
}

void * result_identity(void * result, void * base){
	return base;
}

void * add_acum(void * result, void * base, void * dependencies){
	return base;
}

void * get_0(void * base){
	*(long*) base = 0;
	return base;
}

accumulator accumulator_sum_long() {
	accumulator ac = {int_type,long_type,long_type,
			get_mem_sm(long_type.size),get_0,sum_long_int,result_identity,is_done_false};
	return ac;
}

void * accumulate_left(const stream st, accumulator ac){
	ac.initial_value(ac.base_state);
	while(stream_has_next(st)){
		ac.add(ac.base_state,stream_next(st));
	}
	return ac.result(get_mem_sm(ac.result_type.size),ac.base_state);
}

void accumulate_right_private(stream * st, accumulator * ac){
	if(stream_has_next(*st)){
		void * r = stream_next(*st);
		void * value = get_value_sm(ac->element_type.size,r);
		accumulate_right_private(st,ac);
		ac->add(ac->base_state,value);
	} else {
		ac->initial_value(ac->base_state);
	}
}

void * accumulate_right(stream * st, accumulator * ac){
	accumulate_right_private(st,ac);
	return ac->result(get_mem_sm(ac->result_type.size),ac->base_state);
}
