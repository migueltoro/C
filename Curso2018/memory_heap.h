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
#include <assert.h>
#include <stdlib.h>


typedef struct {
	int size;
	int tam;
	void ** elements;
} memory_heap;


memory_heap memory_heap_create();
void * to_data(void * source, int size, memory_heap * heap);

void memory_heap_free(memory_heap * heap);

#endif /* MEMORY_HEAP_H_ */
