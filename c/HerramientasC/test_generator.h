/*
 * test_generator.h
 *
 *  Created on: 24 ago. 2018
 *      Author: migueltoro
 */

#ifndef TEST_GENERATOR_H_
#define TEST_GENERATOR_H_

#include <stddef.h>
#include <stdio.h>
#include "generator.h"


typedef struct {
	 float x;
}value_test;

typedef struct {
	float min_x;
	float max_x;
	float inc_x;
	float min_y;
	float max_y;
	float inc_y;
	float p_x;
	float p_y;
} parameters_test;

generator get_generator_test(parameters_test * p);

#endif /* TEST_GENERATOR_H_ */
