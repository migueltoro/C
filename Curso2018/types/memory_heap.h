/*
 * memory_heap.h
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */

#ifndef MEMORY_HEAP_H_
#define MEMORY_HEAP_H_

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "../types/preconditions.h"

;
typedef struct {
	int size;
	int tam;
	void ** elements;
} memory_heap;


memory_heap memory_heap_create();
void * memory_heap_copy_and_mem(memory_heap * heap, void * source, int size);
void * memory_heap_get_memory(memory_heap * heap,int size);

void memory_heap_free(memory_heap * heap);

#endif /* MEMORY_HEAP_H_ */
