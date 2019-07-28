/*
 * set.c
 *
 *  Created on: 28 abr. 2019
 *      Author: migueltoro
 */

#include "../types/set.h"
#include "../types/list.h"

set set_empty(type type_element){
	set st = {hash_table_empty(type_element,null_type),memory_heap_create(),type_element};
	return st;
}

set set_of(list * ls){
	set st = set_empty(ls->type_element);
	for(int i =0;i <ls->size;i++){
		set_add_pointer(&st,list_get(ls,i));
	}
	return st;
}

void set_add_pointer(set * st, void * element){
	hash_table_put_pointer(&(st->hash_table),element,NULL);
}

void set_add(set * st, void * element){
	void * e = memory_heap_copy_and_mem(&(st->hp),element,st->type_element.size);
	set_add_pointer(st,e);
}

void set_remove(set * st, void * element){
	hash_table_remove(&(st->hash_table),element);
}

int set_size(set * st){
	return hash_table_size(&(st->hash_table));
}

bool set_contains(set * st, void * element){
	return hash_table_contains(&(st->hash_table),element);
}

iterator set_iterable(set * st){
	st->iterable = hash_table_items_iterable(&st->hash_table);
	iterator im = iterable_map(&st->iterable,0,pair_to_key);
	return im;
}

char * set_tostring(set * st, char * mem){
	iterator it = set_iterable(st);
	return iterable_tostring(&it,st->type_element.tostring,mem);
}

void set_free(set * st){
	hash_table_free(&(st->hash_table));
}

set complete_set() {
	int tam = 50;
	set st = set_empty(double_type);
	for (int i = 0; i < tam; i++) {
		double a2 = get_double_aleatorio(0, 1000) / 2;
		set_add(&st, &a2);
	}
	return st;
}

void test_set() {
	char mem[1000];
	new_rand();
	set st = complete_set();
	printf("%d\n", set_size(&st));
	set_tostring(&st, mem);
	printf("%s\n", mem);
	set_free(&st);
}
