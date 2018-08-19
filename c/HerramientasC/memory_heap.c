/*
 * memory_heap.c
 *
 *  Created on: 10 ago. 2018
 *      Author: migueltoro
 */

#include "memory_heap.h"

memory_heap * memory_heap_add(memory_heap * heap, void * element);

void grow_memory_heap(memory_heap * heap) {
	if (heap->size == heap->tam) {
		heap->tam = 2* heap->tam;
		heap->elements = (void *) realloc(heap->elements, sizeof(void *)*heap->tam);
		assert(heap->elements != NULL);
	}
}

memory_heap memory_heap_create() {
	memory_heap r = { 0, 10, malloc(10 * sizeof(void *)) };
	return r;
}

memory_heap * memory_heap_add(memory_heap * heap, void * element) {
	grow_memory_heap(heap);
	heap->elements[heap->size] = element;
	heap->size = heap->size + 1;
	return heap;
}

void * int_memory(memory_heap * heap, int a) {
	int * element = (int *) malloc(sizeof(int));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}

void * long_memory(memory_heap * heap, long a) {
	long * element = (long *) malloc(sizeof(long));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}

void * float_memory(memory_heap * heap, float a) {
	float * element = (float *) malloc(sizeof(float));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}

void * double_memory(memory_heap * heap, double a) {
	double * element = (double *) malloc(sizeof(double));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}

void  * tuple2_int_memory(memory_heap * heap, int key, int value){
	tuple2 * element = (tuple2 *) malloc(sizeof(tuple2));
	element->key_type = int_type;
	element->value_type = int_type;
	void * pkey = int_memory(heap,key);
	void * pvalue = int_memory(heap,value);
	element->key = pkey;
	element->value = pvalue;
	memory_heap_add(heap, element);
	return element;
}

void * tuple2_double_memory(memory_heap * heap, double key, double value) {
	tuple2 * element = (tuple2 *) malloc(sizeof(tuple2));
	element->key_type = double_type;
	element->value_type = double_type;
	void * pkey = double_memory(heap,key);
	void * pvalue = double_memory(heap,value);
	element->key = pkey;
	element->value = pvalue;
	memory_heap_add(heap, element);
	return element;
}

void * value_memory(memory_heap * heap, int size, void * value) {
	void * element = (void *) malloc(size);
	memcpy(element,value,size);
	memory_heap_add(heap, element);
	return element;
}

void * tam_memory(memory_heap * heap, int size) {
	void * element = (void *) malloc(size);
	memory_heap_add(heap, element);
	return element;
}

void  int_copy(void * target, void * source) {
	*(int *) target = *(int*)source;
}
void  long_copy(void * target, void * source){
	*(long *) target = *(long*)source;
}

void  float_copy(void * target, void * source) {
	*(float *) target = *(float*)source;
}
void  double_copy(void * target, void * source) {
	*(double *) target = *(double*)source;
}
void  tuple2_copy(void * target, void * source) {
	tuple2 * t_source = (tuple2 *) source;
	tuple2 * t_target = (tuple2 *) target;
	t_target->key = t_source->key;
	t_target->key_type = t_source->key_type;
	t_target->value = t_source->value;
	t_target->value_type = t_source->value_type;
}


void memory_heap_free(memory_heap * heap) {
	for (int i = 0; i < heap->size; i++) {
		free(heap->elements[i]);
	}
	free(heap->elements);
}
