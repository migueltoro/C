/*
 * sorted_list.c
 *
 *  Created on: 1 nov. 2018
 *      Author: migueltoro
 */

#include "../types/list.h"

void swap_in_list(list * ls, int a, int b);


void swap_in_list(list * ls, int a, int b){
	void * tmp = ls->elements[a];
	ls->elements[a] = ls->elements[b];
	ls->elements[b] = tmp;
}

#define tam_default 20

void list_grow(list * list) {
	if (list->size == list->tam) {
		list->tam = 2 * list->tam;
		list->elements = realloc(list->elements,list->tam *sizeof(void *));
		assert(list->elements != NULL);
	}
}

list list_empty(type type_element){
	list r = {false,type_element,0,tam_default,malloc(tam_default*sizeof(void *)),memory_heap_create()};
	return r;
}

list list_empty_tam(type type_element,int tam){
	list r = {false,type_element,0,tam,malloc(tam*sizeof(void *)),memory_heap_create()};
	return r;
}

list list_of(void * data, int size, type type_element){
	list r = {false,type_element,0,size,malloc(size*sizeof(void *)),memory_heap_create()};
	char * d = (char *) data;
	for(int i=0; i<size;i++){
		r.elements[i] = d+i*r.type_element.size;
	}
	r.size = size;
	r.tam = size;
	return r;
}

list list_of_pchar(char ** data, int size){
	list ls = list_empty(string_type);
	for(int i=0; i<size;i++){
		string s = string_of_pchar(data[i]);
		list_add(&ls,&s);
	}
	return ls;
}

list list_sublist(list * ls, int a, int b){
	check_position_index(a,ls->size,__FILE__,__LINE__);
	check_position_index(b,ls->size,__FILE__,__LINE__);
	check_argument(b>a,__FILE__,__LINE__,"limites inconsistentes");
	list r = {true,ls->type_element,b-a,b-a,ls->elements+a,ls->hp};
	return r;
}

void * list_get(list * list, const int index){
	check_element_index(index,list->size,__FILE__,__LINE__);
	return list->elements[index];
}

char * list_get_string(list * ls, const int index, char * mem){
	return ls->type_element.tostring(list_get(ls,index),mem);
}

int list_size(list * ls){
	return ls->size;
}

type list_type = {NULL,list_tostring,NULL,NULL,sizeof(list)};

void list_add_pointer(list * list, void * element) {
	check_argument(!list->is_view,__FILE__,__LINE__,"no se puede modificar una vista");
	list_grow(list);
	list->elements[list->size] = element;
	list->size = list->size + 1;
}

void list_add(list * ls, void * element){
	check_argument(!ls->is_view,__FILE__,__LINE__,"no se puede modificar una vista");
	void * e = memory_heap_copy_and_mem(&(ls->hp),element,ls->type_element.size);
	list_add_pointer(ls,e);
}

list list_filter(list * ls, bool (*predicate)(void * e), int sizeElement){
	list r = list_empty(ls->type_element);
	for(int i =0; i< ls->size; i++){
		void * e = list_get(ls,i);
		if(predicate(e)){
			list_add(&r,e);
		}
	}
	return r;
}

list list_map(list * ls, void * (*f)(void * out, void * in), type type_element) {
	list r = list_empty(type_element);
	for (int i = 0; i < ls->size; i++) {
		void * e = list_get(ls, i);
		char temp[type_element.size];
		f(temp,e);
		list_add(&r, temp);
	}
	return r;
}


typedef struct{
	list * ls;
	int i;
}dependencies_list;

bool iterable_list_has_next(iterator * current_iterable) {
	dependencies_list * dp = (dependencies_list *) current_iterable->dependencies;
	return dp->i < list_size(dp->ls);
}

void * iterable_list_see_next(iterator * current_iterable){
	dependencies_list * dp = (dependencies_list *) current_iterable->dependencies;
    return list_get(dp->ls,dp->i);
}

void * iterable_list_next(iterator * current_iterable){
	dependencies_list * dp = (dependencies_list *) current_iterable->dependencies;
	int old_i = dp->i;
	dp->i = dp->i +1;
	return list_get(dp->ls,old_i);
}

iterator list_iterable(list * ls){
	dependencies_list dl = {ls,0};
	int size_dl = sizeof(dependencies_list);
	iterator s_list = iterable_create(sizeof(void *),iterable_list_has_next,iterable_list_next,iterable_list_see_next,NULL,&dl,size_dl);
	return s_list;
}

char * list_tostring(list * ls, char * mem){
	iterator st = list_iterable(ls);
	return iterable_tostring(&st,ls->type_element.tostring,mem);
}


void write_list_to_file(char * file, list * list, char * tostring(const void * source, char * mem)) {
	char mem[256];
	FILE * f = fopen(file, "wt");
	for (int i = 0; i < list->size; i++) {
		fprintf(f, "%s\n", tostring(list_get(list, i), mem));
	}
	fclose(f);
}

list list_of_string_of_file(char * file){
	list r = list_empty(string_type);
	iterator f = file_iterable_pchar(file);
	while(iterable_has_next(&f)){
		char * s = iterable_next(&f);
		remove_eol_s(s);
		string st = string_of_pchar(s);
		list_add(&r,&st);
	}
	return r;
}

void list_free(list * list){
	free(list->elements);
	memory_heap_free(&(list->hp));
}

void list_free_2(list * ls, void (*f)(void * in)){
	for(int i = 0; i < ls->size; i++){
		f(list_get(ls,i));
	}
	list_free(ls);
}

list merge_list(list * ls1, list * ls2, int (*order)(const void * e1, const void * e2)) {
	list ls3 = list_empty(ls1->type_element);
	int s1 = ls1->size;
	int k1 = 0;
	int s2 = ls2->size;
	int k2 = 0;
	while (k1 < s1 || k2 <s2) {
		if (k1 < s1 && k2 < s2) {
			void * e1 = list_get(ls1,k1);
			void * e2 = list_get(ls2,k2);
			if (order(e1, e2) <= 0) {
				list_add_pointer(&ls3,e1);
				k1++;
			} else {
				list_add_pointer(&ls3,e2);
				k2++;
			}
		} else if (k2 == s2) {
			void * e1 = list_get(ls1,k1);
			list_add_pointer(&ls3,e1);
			k1++;
		} else {
			void * e2 = list_get(ls2,k2);
			list_add_pointer(&ls3,e2);
			k2++;
		}
	}
	return ls3;
}

int bs_g(list * ls, int i,int j, void * key, int (*order)(const void * e1, const void * e2));

int bs(list * ls, void* key, int (*order)(const void * e1, const void * e2)){
		return bs_g(ls,0,ls->size,key,order);
}

int bs_g(list * ls, int i, int j, void* key, int (*order)(const void * e1, const void * e2)) {
	assert(j >= i);
	int r;
	int k;
	if (j - i == 0) {
		r = -1;
	} else {
		k = (i + j) / 2;
		int r1 = order(key, list_get(ls,k));
		if (r1 == 0) {
			r = k;
		} else if (r1 < 0) {
			r = bs_g(ls, i, k, key, order);
		} else {
			r = bs_g(ls, k + 1, j, key, order);
		}
	}
	return r;
}

void * piv(list * ls, int i, int j){
	void *  pivote = list_get(ls,get_entero_aleatorio(i, j));
	return pivote;
}

bool inv(list * ls, void * p, int a, int b, int c, int (*order)(const void * e1, const void * e2)) {
	bool r = true;
	for (int i = 0; i < ls->size; i++) {
		if (i < a) {
			r = r && order(list_get(ls, i), p) < 0;
		} else if (i>=a && i < b) {
			r = r && order(list_get(ls, i), p) == 0;
		} else if (i >= c) {
			r = r && order(list_get(ls, i), p) > 0;
		}
	}
	return r;
}

int_pair bh(list * ls, void * pivot, int i, int j, int (*order)(const void * e1, const void * e2)) {
	int a =i, b=i, c=j;
	while (c - b > 0) {
		void * elem = list_get(ls,b);
		int r = order(elem, pivot);
		if (r < 0) {
			swap_in_list(ls,a,b);
			a++;
			b++;
		} else if (r > 0) {
			swap_in_list(ls,b,c-1);
			c--;
		} else {
			b++;
		}
	}
	int_pair r = {a, b};
	return r;
}


void basic_sort_g(list * ls, int inf, int sup, int (*order)(const void * e1, const void * e2)) {
	for (int i = inf; i < sup; i++) {
		for (int j = i + 1; j < sup; j++) {
			if (order(list_get(ls, i), list_get(ls, j)) > 0) {
				swap_in_list(ls,i,j);
			}
		}
	}
}

void basic_sort(list * ls, int (*order)(const void * e1, const void * e2)){
	return basic_sort_g(ls,0,ls->size,order);
}

void list_sort_g(list * ls, int i, int j, int (*order)(const void * e1, const void * e2));

void list_sort(list * ls, int (*order)(const void * e1, const void * e2)){
	list_sort_g(ls,0,ls->size,order);
}

void list_sort_g(list * ls, int i, int j, int (*order)(const void * e1, const void * e2)) {
	assert(j >= i);
	if (j - i <= 4) {
		basic_sort_g(ls, i, j, order);
	} else {
		void * pivote = piv(ls,i,j);
		int_pair p = bh(ls, pivote, i, j, order);
		list_sort_g(ls, i, p.a, order);
		list_sort_g(ls, p.b, j, order);
	}
}

int string_naturalorder_punt(const void * e1, const void * e2) {
	void ** r1 = (void **) e1;
	void ** r2 = (void **) e2;
	char * a1 = (char *) * r1;
	char * a2 = (char *) * r2;
	return strcmp(a1, a2);
}

void test_list() {
	char mem[1000];
	list ls1 = list_empty(double_type);
	for (int i = 0; i < 50; i++) {
		double r = 1. * get_entero_aleatorio(0, 100);
		list_add(&ls1,&r);
	}
	list ls2 = list_empty(double_type);
	for (int i = 0; i < 50; i++) {
		double r = 1. * get_entero_aleatorio(0, 100);
		list_add(&ls2, &r);
	}
	double a = -340.51;
	list_add(&ls2, &a);
	list_add(&ls1, &a);
	list ls2s = list_sublist(&ls2,10,20);
	list_sort(&ls1, double_naturalorder);
	list_sort(&ls2s, double_naturalorder);
	char * s = list_tostring(&ls1, mem);
	printf("ls1 = %s\n", s);
	s = list_tostring(&ls2, mem);
	printf("ls2 = %s\n", s);
	s = list_tostring(&ls2s, mem);
	printf("ls2s = %s\n", s);
	list ls3 = merge_list(&ls1, &ls2s, double_naturalorder);
	s = list_tostring(&ls3, mem);
	printf("ls3 = %s\n", s);
	double d[] = {2.,3.,4.5,5.7,8.9,-3.1};
	list ls4 = list_of(d,6,double_type);
	s = list_tostring(&ls4, mem);
	printf("ls4 = %s\n", s);
	char * as[] = {"Hola","Juan","Antonio","Pepe","Juan","Diaz"};
	list ls5 = list_of_pchar(as,6);
	list_sort(&ls5, string_naturalorder);
	s = list_tostring(&ls5,  mem);
	printf("ls5 = %s\n", s);
	list ls = list_of_string_of_file("ficheros/prueba.txt");
	char * s1 = list_get(&ls,2);
	printf("s1 = %s\n", string_tostring(s1,mem));
	s = list_tostring(&ls,mem);
	printf("ls1 = %s\n", s);
	list_free_2(&ls5,string_free);
	list_free_2(&ls,string_free);
	list_free(&ls1);
	list_free(&ls2);
	list_free(&ls3);
	list_free(&ls4);
}
