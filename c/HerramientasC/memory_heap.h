/*
 * memory_heap.h
 *
 *  Created on: 10 ago. 2018
 *      Author: migueltoro
 */

#ifndef MEMORY_HEAP_H_
#define MEMORY_HEAP_H_


#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include "definitions.h"

typedef struct {
	int size;
	int tam;
	void ** elements;
} memory_heap;


memory_heap memory_heap_create();
memory_heap * memory_heap_add(memory_heap * heap, void * element);
void  * value_memory(memory_heap * heap, int size, void * value);
void  * tam_memory(memory_heap * heap, int size);

void memory_heap_free(memory_heap * heap);

#endif /* MEMORY_HEAP_H_ */
