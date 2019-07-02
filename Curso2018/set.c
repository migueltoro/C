/*
 * set.c
 *
 *  Created on: 28 abr. 2019
 *      Author: migueltoro
 */

#include "set.h"

#include "list.h"

set set_empty(
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem)){
	set st = {hash_table_empty(equals,tostring),memory_heap_create()};
	return st;
}

set set_of(list * ls,
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem)){
	set st = set_empty(equals,tostring);
	for(int i =0;i <ls->size;i++){
		set_add_pointer(&st,list_get(ls,i));
	}
	return st;
}

void set_add_pointer(set * st, void * element){
	hash_table_put_pointer(&(st->hash_table),element,NULL);
}

void set_add(set * st, void * element, int sizeElement){
	void * e = memory_heap_to_data(&(st->hp),element,sizeElement);
	set_add_pointer(st,e);
}

int set_size(set * st){
	return hash_table_size(&(st->hash_table));
}

bool set_contains(set * st, void * element){
	return hash_table_contains(&(st->hash_table),element);
}

char * set_tostring(set * st, char * to_string(const void * source, char * mem), char * mem) {
	hash_table * table = &(st->hash_table);
	sprintf(mem, "\n{");
	char mkey[256];
	int i, j;
	int blocks_not_empty = 0;
	bool firstElement = true;
	for (i = 0; i < table->capacity_blocks; i++) {
		int first = table->blocks[i];
		if (first < 0) continue;
		blocks_not_empty++;
		j = first;
		while (j >= 0) {
			void * key = table->data[j].key;
			if(firstElement)  firstElement = false;
			else strcat(mem,",");
			sprintf(mkey, "%s", table->tostring_key(key, mkey));
			strcat(mem,mkey);
			j = table->data[j].next;
		}
	}
	strcat(mem,"}\n");
	return mem;
}

void set_free(set * st){
	hash_table_free(&(st->hash_table));
}

void test_set() {
	int tam = 50;
	char mem[1000];
	new_rand();
	set st = set_empty(double_equals, double_tostring);
	for (int i = 0; i < tam; i++) {
		double a2 = get_double_aleatorio(0, 1000)/2;
		set_add(&st,&a2,sizeof(double));
	}
	printf("%d",set_size(&st));
	set_tostring(&st,double_tostring,mem);
	printf("%s",mem);
	set_free(&st);
}
