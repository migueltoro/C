/*
 * sorted_list.c
 *
 *  Created on: 1 nov. 2018
 *      Author: migueltoro
 */

#include "list.h"

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

list list_empty(){
	list r = {0,tam_default,malloc(tam_default*sizeof(void *)),memory_heap_create()};
	return r;
}

list list_empty_tam(int tam){
	list r = {0,tam,malloc(tam*sizeof(void *)),memory_heap_create()};
	return r;
}

list list_of(void * data, int size, int sizeElement){
	list r = {0,size,malloc(size*sizeof(void *)),memory_heap_create()};
	char * d = (char *) data;
	for(int i=0; i<size;i++){
		r.elements[i] = d+i*sizeElement;
	}
	r.size = size;
	r.tam = size;
	return r;
}

void * list_get(list * list, const int index){
	assert(index < list->size && "index out of range");
	return list->elements[index];
}

int list_size(list * ls){
	return ls->size;
}

void list_add_pointer(list * list, void * element) {
	list_grow(list);
	list->elements[list->size] = element;
	list->size = list->size + 1;
}

void list_add(list * ls, void * element, int size_element){
	void * e = memory_heap_to_data(&(ls->hp),element,size_element);
	list_add_pointer(ls,e);
}

list list_filter(list * ls, bool (*predicate)(void * e), int sizeElement){
	list r = list_empty();
	for(int i =0; i< ls->size; i++){
		void * e = list_get(ls,i);
		if(predicate(e)){
			list_add(&r,e,sizeElement);
		}
	}
	return r;
}

list list_map(list * ls, void * (*f)(void * e), int sizeElement) {
	list r = list_empty();
	for (int i = 0; i < ls->size; i++) {
		void * e = list_get(ls, i);
		void * t = f(e);
		list_add(&r, t, sizeElement);
	}
	return r;
}

char * list_tostring(list * list, char * to_string(const void * source, char * tp), char * mem) {
	char nm[256];
	strcpy(mem,"{");
	for(int i = 0; i < list->size; i++) {
		char * r = to_string(list->elements[i],nm);
		if(i>0) strcat(mem,",");
		strcat(mem,r);
	}
	strcat(mem,"}");
	return mem;
}

void list_free(list * list){
	free(list->elements);
	memory_heap_free(&(list->hp));
}

list merge_list(list * ls1, list * ls2, int (*order)(const void * e1, const void * e2)) {
	list ls3 = list_empty();
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

int bs2(list * ls, int i,int j, void * key, int (*order)(const void * e1, const void * e2));

int bs(list * ls, void* key, int (*order)(const void * e1, const void * e2)){
		return bs2(ls,0,ls->size,key,order);
}

int bs2(list * ls, int i,int j, void* key, int (*order)(const void * e1, const void * e2)) {
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
			r = bs2(ls, i, k, key, order);
		} else {
			r = bs2(ls, k + 1, j, key, order);
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


void basic_sort(list * ls, int inf, int sup, int (*order)(const void * e1, const void * e2)) {
	for (int i = inf; i < sup; i++) {
		for (int j = i + 1; j < sup; j++) {
			if (order(list_get(ls, i), list_get(ls, j)) > 0) {
				swap_in_list(ls,i,j);
			}
		}
	}
}

void list_sort_2(list * ls, int i, int j, int (*order)(const void * e1, const void * e2));

void list_sort(list * ls, int (*order)(const void * e1, const void * e2)){
	list_sort_2(ls,0,ls->size,order);
}

void list_sort_2(list * ls, int i, int j, int (*order)(const void * e1, const void * e2)) {
	assert(j >= i);
	if (j - i <= 4) {
		basic_sort(ls, i, j, order);
	} else {
		void * pivote = piv(ls,i,j);
		int_pair p = bh(ls, pivote, i, j, order);
		list_sort_2(ls, i, p.a, order);
		list_sort_2(ls, p.b, j, order);
	}
}

void test_list() {
	char mem[500];
	list ls1 = list_empty(sizeof(double));
	for (int i = 0; i < 50; i++) {
		double r = 1. * get_entero_aleatorio(0, 100);
		list_add(&ls1,&r,sizeof(double));
	}
	list ls2 = list_empty(sizeof(double));
	for (int i = 0; i < 30; i++) {
		double r = 1. * get_entero_aleatorio(0, 100);
		list_add(&ls2, &r,sizeof(double));
	}
	list_sort(&ls1, double_naturalorder);
	list_sort(&ls2, double_naturalorder);
	char * s = list_tostring(&ls1, double_tostring, mem);
	printf("ls1 = %s\n", s);
	s = list_tostring(&ls2, double_tostring, mem);
	printf("ls2 = %s\n", s);
	list ls3 = merge_list(&ls1, &ls2, double_naturalorder);
	s = list_tostring(&ls3, double_tostring, mem);
	printf("ls3 = %s\n", s);
	double d[] = {2.,3.,4.5,5.7,8.9,-3.1};
	list ls4 = list_of(d,6,sizeof(double));
	s = list_tostring(&ls4, double_tostring, mem);
	printf("ls4 = %s\n", s);
	string as[] = {"Hola","Juan","Antonio","Pepe","Juan","Diaz"};
	list ls5 = list_of(as,6,sizeof(string));
	s = list_tostring(&ls5, string_tostring, mem);
	printf("ls5 = %s\n", s);
}
