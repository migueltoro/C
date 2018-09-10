/*
 * test_generator.c
 *
 *  Created on: 24 ago. 2018
 *      Author: migueltoro
 */


#include "test_generator.h"


bool iterate_test_3(generator * ge) {
	parameters_test * p = (parameters_test *) ge->parameters;
	START(ge);
	for (p->p_x = p->min_x;p->p_x < p->max_x; p->p_x = p->p_x + p->inc_x){
		for (p->p_y = p->min_y;p->p_y < p->max_y; p->p_y = p->p_y + p->inc_y){
			*(float *) ge->values = p->p_x*p->p_y;
			YIELD(ge);
		}
	}
	FINISH;
	return false;
}

//bool iterate_test_e(generator * ge) {
//	static parameters_test p = {10,20,3,0};
////	START(ge);
////	#define START(gg) switch(gg->state) { case 0:
//	switch(ge->state) { case 0: ;
//	p.v = p.min_x;
//	while (p.v < p.max_x) {
////			GG_DATA_PROPERTY(ge,value_test,x) = x;
////          #define GG_DATA_PROPERTY(gg,t_value,propiety) ((t_value *) gg->value_state)->propiety
//			((value_test *) ge->values)->x = p.v;
////			YIELD(ge);
////  #define YIELD(gg) do {gg->state = __LINE__; return (true); case __LINE__:; } while (false)
//			do { ge->state = __LINE__; return (true); case __LINE__:; } while (false) ;
//			p.v = p.v +p.inc_x;
//	}
////	FINISH;
////  #define break; default:; }
////	break;
//	default:; } ;
//	return false;
//}



generator get_generator_test(parameters_test * p){
	generator ge = {0,iterate_test_3,malloc(sizeof(float)),&float_type,NULL};
	ge.parameters = p;
	return ge;
}


