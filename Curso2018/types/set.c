/*
 * set.c
 *
 *  Created on: 28 abr. 2019
 *      Author: migueltoro
 */

#include "../types/set.h"

#include "../types/list.h"

set set_empty(type type_element){
	set st = {hash_table_empty(type_element,0),memory_heap_create()};
	return st;
}

set set_of(list * ls, type type_element){
	set st = set_empty(type_element);
	for(int i =0;i <ls->size;i++){
		set_add_pointer(&st,list_get(ls,i));
	}
	return st;
}

void set_add_pointer(set * st, void * element){
	hash_table_put_pointer(&(st->hash_table),element,NULL);
}

void set_add(set * st, void * element){
	void * e = memory_heap_to_data(&(st->hp),element,st->type_element.size);
	set_add_pointer(st,e);
}

int set_size(set * st){
	return hash_table_size(&(st->hash_table));
}

bool set_contains(set * st, void * element){
	return hash_table_contains(&(st->hash_table),element);
}


typedef struct{
	iterable st;
}dependencies_set;

bool iterable_set_has_next(iterable * current_iterable) {
	dependencies_set * dp = (dependencies_set *) current_iterable->dependencies;
	return iterable_has_next(&dp->st);
}

void * iterable_set_see_next(iterable * current_iterable){
	dependencies_set * dp = (dependencies_set *) current_iterable->dependencies;
	void * key = ((pair_t *)iterable_see_next(&dp->st))->key;
	return key;
}

void * iterable_set_next(iterable * current_iterable){
	dependencies_set * dp = (dependencies_set *) current_iterable->dependencies;
	void * key = ((pair_t *)iterable_next(&dp->st))->key;
	return key;
}

iterable set_iterable(set * st){
	dependencies_set ds = {hash_table_items_iterable(&st->hash_table)};
	int size_ds = sizeof(dependencies_set);
	iterable s_set = create_iterable(sizeof(void *),iterable_set_has_next,iterable_set_next,iterable_set_see_next,&ds,size_ds);
	return s_set;
}

char * set_tostring(set * st, char * mem){
	iterable it = set_iterable(st);
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
	printf("%d", set_size(&st));
	set_tostring(&st, mem);
	printf("%s", mem);
	iterable is = set_iterable(&st);
	iterable_toconsole_sep(&is, double_tostring, "\n", "__________________\n",
			"\n_______________\n");
	printf("%s", set_tostring(&st, mem));
	set_free(&st);
}
