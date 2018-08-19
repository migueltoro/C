/*
 * list.c
 *
 *  Created on: 10 ago. 2018
 *      Author: migueltoro
 */

#include "basic_types.h"
#include "list.h"
#include "stream.h"
#include "memory_heap.h"
#include "library.h"

memory_heap list_memory = {0,0,NULL};

memory_heap * get_list_memory(){
	if(list_memory.elements == NULL) {
		list_memory = memory_heap_create();
	}
	return &list_memory;
}

void * get_mem_list(int size){
	return tam_memory(get_list_memory(),size);
}

void * get_value_list(int size, void * value){
	return value_memory(get_list_memory(),size, value);
}

void list_memory_clear(){
	memory_heap_free(&list_memory);
}

type list_type = {sizeof(list),NULL,NULL,NULL,NULL,"alist_type"};

void grow_list(list * list) {
	if(list->size == list->tam){
		list->tam = 2*list->tam;
		list->elements = (void *) realloc(list->elements,sizeof(void *)*list->tam);
		assert(list->elements != NULL);
	}
}

list list_empty(type element_type){
	list r = {element_type,0,10,malloc(10*sizeof(void *))};
	return r;
}

void * list_get(const list list, const int index) {
	assert(index < list.size);
	return list.elements[index];
}

void list_add(list * list, void * element) {
	grow_list(list);
	list->elements[list->size] = element;
	list->size = list->size+1;
}

void list_set(list * list, int index, void * element) {
	assert(index <= list->size);
	grow_list(list);
	list->elements[index] = element;
	if (index == list->size) list->size = list->size + 1;
}

list list_concat(const list ls1, const list ls2){
	assert(type_equals(ls1.element_type,ls2.element_type));
	list r = list_empty(ls1.element_type);
	for(int i =0; i<ls1.size;i++) list_add(&r,list_get(ls1,i));
	for(int i =0; i<ls1.size;i++) list_add(&r,list_get(ls2,i));
	return r;
}

void list_sort(list * ls, int (*comparator)(const void*, const void*)){
	generic_qsort(ls->elements, 0, ls->size,comparator);
}

void list_sort_naturalorder(list * ls) {
	generic_qsort(ls->elements, 0, ls->size,ls->element_type.naturalorder);
}

typedef struct {
	int index;
	void * element;
} list_stream_state;

typedef struct {
	list ls;
	list_stream_state * old_state;
}list_stream_dependencies;

int list_stream_has_next(void * state,void * dependencies){
	list_stream_dependencies * d = (list_stream_dependencies *) dependencies;
	list_stream_state * s = (list_stream_state *) state;
	return s->index < d->ls.size;
}

void * list_stream_next(void * state, void * dependencies){
	list_stream_dependencies * d = (list_stream_dependencies *) dependencies;
	list_stream_state * s = (list_stream_state *) state;
	int index = s->index;
	d->old_state->index = index;
	void * r = list_get(d->ls,index);
	d->old_state->element = r;
	s->index = index +1;
	return d->old_state->element;
}

stream list_stream(list ls) {
	list_stream_dependencies dp = {ls, get_mem_list(sizeof(list_stream_state))};
	list_stream_state initial_state ={0, get_mem_list(sizeof(void *))};
	stream sm = stream_create(ls.element_type,
			get_value_list(sizeof(list_stream_state),&initial_state),
			list_stream_has_next, list_stream_next,
			get_value_list(sizeof(list_stream_dependencies), &dp));
	return sm;
}

