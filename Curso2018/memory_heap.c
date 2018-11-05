/*
 * memory_heap.c
 *
 *  Created on: 5 nov. 2018
 *      Author: migueltoro
 */


#include "memory_heap.h"

void grow_memory_heap(memory_heap * heap) {
	if (heap->size == heap->tam) {
		heap->tam = 2* heap->tam;
		heap->elements = (void *) realloc(heap->elements, sizeof(void *)*heap->tam);
		assert(heap->elements != NULL && "no se ha podido reubicar la memoria");
	}
}

memory_heap memory_heap_create() {
	memory_heap r = {0, 10, malloc(10 * sizeof(void *)) };
	return r;
}

memory_heap * memory_heap_add(memory_heap * heap, void * element) {
	grow_memory_heap(heap);
	heap->elements[heap->size] = element;
	heap->size = heap->size + 1;
	return heap;
}

void * to_data(void * source, int sizeElement, memory_heap * heap){
	void * element = (void *) malloc(sizeElement);
	memcpy(element,source,sizeElement);
	memory_heap_add(heap, element);
	return element;
}

void memory_heap_free(memory_heap * heap) {
	for (int i = 0; i < heap->size; i++) {
		free(heap->elements[i]);
	}
	free(heap->elements);
}
