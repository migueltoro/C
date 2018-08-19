/*
 * library.h
 *
 *  Created on: 15 ago. 2018
 *      Author: migueltoro
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "basic_types.h"
#include "string_buffer.h"


void * yields(void * value);

void print_array(string_buffer * buffer, void * b[], int low, int height, type type);

void generic_qsort(void **arr, int lo, int hi, int (*compare)(const void *, const void*));

#endif /* LIBRARY_H_ */
