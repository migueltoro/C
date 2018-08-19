/*
 * memory_heap.h
 *
 *  Created on: 10 ago. 2018
 *      Author: migueltoro
 */

#ifndef MEMORY_HEAP_H_
#define MEMORY_HEAP_H_


#include "basic_types.h"


typedef struct {
	int size;
	int tam;
	void ** elements;
} memory_heap;


memory_heap memory_heap_create();
void  * int_memory(memory_heap * heap, int a);
void  * long_memory(memory_heap * heap, long a);
void  * float_memory(memory_heap * heap, float a);
void  * double_memory(memory_heap * heap, double a);
void  * tuple2_int_memory(memory_heap * heap, int a, int b);
void  * tuple2_double_memory(memory_heap * heap, double a, double b);
void  * value_memory(memory_heap * heap, int size, void * value);
void  * tam_memory(memory_heap * heap, int size);

void  int_copy(void * target, void * source);
void  long_copy(void * target, void * source);
void  float_copy(void * target, void * source);
void  double_copy(void * target, void * source);
void  tuple2_copy(void * target, void * source);


void memory_heap_free(memory_heap * heap);

#endif /* MEMORY_HEAP_H_ */
