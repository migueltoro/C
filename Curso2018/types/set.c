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
	iterator im = iterable_map(&st->iterable,st->type_element,pair_to_key);
	return im;
}

char * set_tostring(set * st, char * mem){
	iterator it = set_iterable(st);
	return iterable_tostring(&it,st->type_element.tostring,mem);
}

list set_tolist(const set * s) {
	list res = list_empty(s->type_element);
	iterator it = set_iterable(s);
	while(iterable_has_next(&it)) {
		list_add(&res, iterable_next(&it));
	}
	list_sort(&res, s->type_element.order);
	return res;
}

bool set_equals(const set * s1, const set * s2) {
	bool mismo_tipo = type_equals(&s1->type_element, &s2->type_element);
	bool mismo_size = set_size(s1)==set_size(s2);
	bool res = mismo_tipo && mismo_size;
	if(res) {
		list ls1 = set_tolist(s1);
		list ls2 = set_tolist(s2);
		res = list_equals(&ls1, &ls2);
	}
	return res;
}

set * set_parse(set * out, char * text) {
	iterator it = text_to_iterable_pchar(text, "{ ,}");
	while(iterable_has_next(&it)) {
		set_add(out, iterable_next(&it));
	}
	iterable_free(&it);
	return out;
}

set set_parse_s(char * text) {
	set res = set_empty(pchar_type);
	iterator it = text_to_iterable_pchar(text, "{ ,}");
	while(iterable_has_next(&it)) {
		set_add(&res, iterable_next(&it));
	}
	iterable_free(&it);
	return res;
}

type set_type = {set_equals, set_tostring, NULL, set_parse, sizeof(set)};


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

void test_set_2() {
	puts("\n\n------------------------------ TEST Set2 ------------------------------");

	int size = 10;
	int* enteros = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) {
		*(enteros + i) = i;
	}
	list ls = list_of(enteros, size, int_type);
	set s1 = set_of(&ls);
	set s2 = set_of(&ls);

	char* mem1 = malloc(512 * sizeof(char));
	char* mem2 = malloc(512 * sizeof(char));
	printf("\n¿Son iguales s1 y s2?: %s; s1=%s; s2=%s\n",
			MSG_BOOL(set_equals(&s1, &s2)), set_tostring(&s1, mem1),
			set_tostring(&s2, mem2));

	int valor = 11;
	set_add(&s2, &valor);
	printf("¿Son iguales s1 y s2?: %s; s1=%s; s2=%s\n",
			MSG_BOOL(set_equals(&s1, &s2)), set_tostring(&s1, mem1),
			set_tostring(&s2, mem2));

	char* texto1 = "{Estas, son, pruebas, de, nuevas, funciones, para, el, tipo, set}";
	set s4 = set_empty(pchar_type);
	set_parse(&s4, texto1);
	printf("Dada la cadena \"%s\", set_parse ha obtenido el conjunto:\n%s\n",
			texto1, set_tostring(&s4, mem1));

	char* texto2 = "{Creo, que, todo, todo, todo, funciona, bien, bien}";
	set s5 = set_parse_s(texto2);
	printf("Dada la cadena \"%s\", set_parse_s ha obtenido la lista:\n%s\n",
			texto2, set_tostring(&s5, mem1));
}
