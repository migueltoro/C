/*
 * sorted_list.c
 *
 *  Created on: 1 nov. 2018
 *      Author: migueltoro
 */

#include "sorted_list.h"

void swap_in_list(alist * ls, int a, int b);


void swap_in_list(alist * ls, int a, int b){
	void * tmp = ls->elements[a];
	ls->elements[a] = ls->elements[b];
	ls->elements[b] = tmp;
}

#define tam_default 20

void alist_grow(alist * list) {
	if (list->size == list->tam) {
		list->tam = 2 * list->tam;
		list->elements = realloc(list->elements,list->tam *sizeof(void *));
		assert(list->elements != NULL);
	}
}

alist alist_empty(){
	alist r = {0,tam_default,malloc(tam_default*sizeof(void *))};
	return r;
}

alist alist_empty_tam(int tam){
	alist r = {0,tam,malloc(tam*sizeof(void *))};
	return r;
}

alist alist_create(void * data, int size, int sizeElement){
	alist r = {0,size,malloc(size*sizeof(void *))};
	char * d = (char *) data;
	for(int i=0; i<size;i++){
		r.elements[i] = d+i*sizeElement;
	}
	r.size = size;
	r.tam = size;
	return r;
}

void * alist_get(alist * list, const int index){
	assert(index < list->size && "index out of range");
	return list->elements[index];
}

void alist_add(alist * list, void * element) {
	alist_grow(list);
	list->elements[list->size] = element;
	list->size = list->size + 1;
}

alist alist_filter(alist * ls, bool (*predicate)(void * e)){
	alist r = alist_empty();
	for(int i =0; i< ls->size; i++){
		void * e = alist_get(ls,i);
		if(predicate(e)){
			alist_add(&r,e);
		}
	}
	return r;
}

alist alist_map(alist * ls, void * (*f)(void * e)) {
	alist r = alist_empty();
	for (int i = 0; i < ls->size; i++) {
		void * e = alist_get(ls, i);
		void * t = f(e);
		alist_add(&r, t);
	}
	return r;
}

char * alist_tostring(alist * list, char * to_string(const void * source, char * tp), char * mem) {
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

void alist_free(alist * list){
	free(list->elements);
}

alist merge_list(alist * ls1, alist * ls2, int (*order)(const void * e1, const void * e2)) {
	alist ls3 = alist_empty();
	int s1 = ls1->size;
	int k1 = 0;
	int s2 = ls2->size;
	int k2 = 0;
	while (k1 < s1 || k2 <s2) {
		if (k1 < s1 && k2 < s2) {
			void * e1 = alist_get(ls1,k1);
			void * e2 = alist_get(ls2,k2);
			if (order(e1, e2) <= 0) {
				alist_add(&ls3,e1);
				k1++;
			} else {
				alist_add(&ls3,e2);
				k2++;
			}
		} else if (k2 == s2) {
			void * e1 = alist_get(ls1,k1);
			alist_add(&ls3,e1);
			k1++;
		} else {
			void * e2 = alist_get(ls2,k2);
			alist_add(&ls3,e2);
			k2++;
		}
	}
	return ls3;
}

int bs2(alist * ls, int i,int j, void * key, int (*order)(const void * e1, const void * e2));

int bs(alist * ls, void* key, int (*order)(const void * e1, const void * e2)){
		return bs2(ls,0,ls->size,key,order);
}

int bs2(alist * ls, int i,int j, void* key, int (*order)(const void * e1, const void * e2)) {
	assert(j >= i);
	int r;
	int k;
	if (j - i == 0) {
		r = -1;
	} else {
		k = (i + j) / 2;
		int r1 = order(key, alist_get(ls,k));
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

void * piv(alist * ls, int i, int j){
	void *  pivote = alist_get(ls,get_entero_aleatorio(i, j));
	return pivote;
}

bool inv(alist * ls, void * p, int a, int b, int c, int (*order)(const void * e1, const void * e2)) {
	bool r = true;
	for (int i = 0; i < ls->size; i++) {
		if (i < a) {
			r = r && order(alist_get(ls, i), p) < 0;
		} else if (i>=a && i < b) {
			r = r && order(alist_get(ls, i), p) == 0;
		} else if (i >= c) {
			r = r && order(alist_get(ls, i), p) > 0;
		}
	}
	return r;
}

int_pair bh(alist * ls, void * pivot, int i, int j, int (*order)(const void * e1, const void * e2)) {
	int a =i, b=i, c=j;
	while (c - b > 0) {
		void * elem = alist_get(ls,b);
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


void basic_sort(alist * ls, int inf, int sup, int (*order)(const void * e1, const void * e2)) {
	for (int i = inf; i < sup; i++) {
		for (int j = i + 1; j < sup; j++) {
			if (order(alist_get(ls, i), alist_get(ls, j)) > 0) {
				swap_in_list(ls,i,j);
			}
		}
	}
}

void alist_sort_2(alist * ls, int i, int j, int (*order)(const void * e1, const void * e2));

void alist_sort(alist * ls, int (*order)(const void * e1, const void * e2)){
	alist_sort_2(ls,0,ls->size,order);
}

void alist_sort_2(alist * ls, int i, int j, int (*order)(const void * e1, const void * e2)) {
	assert(j >= i);
	if (j - i <= 4) {
		basic_sort(ls, i, j, order);
	} else {
		void * pivote = piv(ls,i,j);
		int_pair p = bh(ls, pivote, i, j, order);
		alist_sort_2(ls, i, p.a, order);
		alist_sort_2(ls, p.b, j, order);
	}
}

void test_list() {
	memory_heap hp = memory_heap_create();
	char mem[500];
	alist ls1 = alist_empty(sizeof(double));
	for (int i = 0; i < 50; i++) {
		double r = 1. * get_entero_aleatorio(0, 100);
		alist_add(&ls1, to_data(&r,sizeof(double),&hp));
	}
	alist ls2 = alist_empty(sizeof(double));
	for (int i = 0; i < 30; i++) {
		double r = 1. * get_entero_aleatorio(0, 100);
		alist_add(&ls2, to_data(&r,sizeof(double),&hp));
	}
	alist_sort(&ls1, double_naturalorder);
	alist_sort(&ls2, double_naturalorder);
	char * s = alist_tostring(&ls1, double_tostring, mem);
	printf("ls1 = %s\n", s);
	s = alist_tostring(&ls2, double_tostring, mem);
	printf("ls2 = %s\n", s);
	alist ls3 = merge_list(&ls1, &ls2, double_naturalorder);
	s = alist_tostring(&ls3, double_tostring, mem);
	printf("ls3 = %s\n", s);
	memory_heap_free(&hp);
	double d[] = {2.,3.,4.5,5.7,8.9,-3.1};
	alist ls4 = alist_create(d,6,sizeof(double));
	s = alist_tostring(&ls4, double_tostring, mem);
	printf("ls4 = %s\n", s);
	string as[] = {"Hola","Juan","Antonio","Pepe","Juan","Diaz"};
	alist ls5 = alist_create(as,6,sizeof(string));
	s = alist_tostring(&ls5, string_tostring, mem);
	printf("ls5 = %s\n", s);
}
