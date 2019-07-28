/*
 * multiset.c
 *
 *  Created on: 25 jul. 2019
 *      Author: migueltoro
 */

#include "../types/multiset.h"
#include "../types/accumulators.h"

multiset multiset_empty(type type_element){
	multiset st = {hash_table_empty(type_element,int_type),memory_heap_create(),type_element};
	return st;
}

multiset multiset_of(list * ls){
	multiset st = multiset_empty(ls->type_element);
	for(int i =0;i <ls->size;i++){
		multiset_add_pointer(&st,list_get(ls,i),1);
	}
	return st;
}

void multiset_add_pointer(multiset * st, void * element, int n) {
	if (hash_table_contains(&st->hash_table, element)) {
		void * count = hash_table_get(&st->hash_table, element);
		*(int *) count = (*(int *) count) + n;
	} else {
		int nn =n;
		void * pn = memory_heap_copy_and_mem(&(st->hp),&nn,sizeof(int));
		hash_table_put_pointer(&st->hash_table,element,pn);
	}
}


void multiset_add(multiset * st, void * element, int n) {
	void * e = memory_heap_copy_and_mem(&(st->hp), element, st->type_element.size);
	multiset_add_pointer(st,e,n);
}

int multiset_size(multiset * st){
	return hash_table_size(&(st->hash_table));
}

bool multiset_contains(multiset * st, void * element){
	return hash_table_contains(&(st->hash_table),element);
}

void multiset_remove(multiset * st, void * element, int nu) {
	if (hash_table_contains(&st->hash_table, element)) {
		void * n = hash_table_get(&st->hash_table, element);
		int m = MAX(*(int*) n -nu, 0);
		if(m>0) *(int*) n = m;
		else hash_table_remove(&st->hash_table, element);
	}
}

int multiset_count(multiset * st, void * element){
	int r =0;
	if (hash_table_contains(&st->hash_table, element)) {
		void * n = hash_table_get(&st->hash_table, element);
	    r = *(int*) n;
	}
	return r;
}

iterator multiset_iterable(multiset * st){
	return hash_table_items_iterable(&st->hash_table);
}

char * multiset_tostring(multiset * st, char * mem){
	return hash_table_tostring(&st->hash_table,mem);
}

void multiset_free(multiset * st){
	hash_table_free(&(st->hash_table));
}

multiset complete_multiset() {
	int tam = 50;
	multiset st = multiset_empty(double_type);
	for (int i = 0; i < tam; i++) {
		double a2 = get_double_aleatorio(0, 1000);
		multiset_add(&st,&a2,i%3+1);
	}
	return st;
}

double * _random(double * out, long * in){
	*out = get_double_aleatorio(0, 100);
	return out;
}

void test_multiset() {
	char mem[1000];
	new_rand();
	multiset st = complete_multiset();
	printf("%d\n", multiset_size(&st));
	char * s = multiset_tostring(&st, mem);
	printf("%s\n",s);
	multiset_free(&st);
}
