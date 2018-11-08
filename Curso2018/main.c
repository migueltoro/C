/*
 ============================================================================
 Name        : Curso2018.c
 Author      : Miguel Toro
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "primeros_ejemplos.h"
#include "sorted_list.h"
#include "types.h"
#include "files.h"
#include "hash_table.h"
#include "memory_heap.h"
#include "binary_tree.h"
#include "dates.h"

void test_ejemplos() {
	string as[] = {"Hola","Juan","Antonio","Pepe","Juan","Diaz"};
	string_list ls5 = create_string_list(as,6,6);
	imprime_list_string(ls5);

	printf("\n\n");

	double d1[] = { 45., 56, 90., 1., 23., 78., 76. };
	double_list ls1 = create_double_list(d1, 7, 7);
	double r1 = problema1(ls1);
	printf("r1 = %lf\n", r1);

	int d3[] = { 45, 57, 10, 1, 23, 77, 79 };
	int_list ls3 = create_int_list(d3, 7, 7);
	bool r3 = problema3(ls3, es_impar);
	printf("r3 = %s\n", r3 ? "true" : "false");

	bool r4 = problema4(ls3, es_impar);
	printf("r4 = %s\n", r4 ? "true" : "false");

	int r5 = problema5(ls3);
	printf("r5 = %d\n", r5);

	double r6 = problema6(ls1, 10.);
	printf("r6 = %lf\n", r6);

	punto ap[] = { { 1., 2. }, { -1., 2.1 }, { 3.1, 2.1 }, { 1.3, 27.0 }, { 1.,
			-2. } };
	punto_list r2 = create_punto_list(ap, 5, 5);
	double_list s = problema2(r2);
	imprime_list_punto(r2, ",", "{", "}");
	printf("\n");
	imprime_list_double(s, ",", "{", "}");
	printf("\n");

	punto * p = problema8(r2, punto_naturalorder);
	printf("(%.2lf,%.2lf)", p->x, p->y);

	printf("\n\n");

	file_iterator f = open_file("prueba.txt");
	while (has_next_line(&f)) {
		printf("%s\n", next_line(&f));
	}
	fclose(f.file);

	printf("\n\n");

	punto_list r7 = list_punto_from_file("prueba.txt");
	imprime_list_punto(r7, ",", "{", "}");

	printf("\n\n");

	printf("Es primo = %s\n", es_primo(29) ? "true" : "false");

	printf("\n\n");

	punto_list r8 = create_punto_list(ap, 5, 5);
	punto_list_list r9 = problema11(r8);
	imprime_list_list_punto(r9, "", "", "");

	problema59("primos.txt", 100);
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

hash_table complete_table(memory_heap * hp) {
	int tam = 100;
	hash_table ht = hash_table_create(long_equals, long_tostring);
	for (int i = 0; i < tam; i++) {
		long a1 = i;
		double a2 = get_double_aleatorio(0, 1000);
		hash_table_put(&ht,to_data(&a1,sizeof(long),hp),  to_data(&a2,sizeof(double),hp));
	}
	for (int i = 2; i < tam; i++) {
		long a1 = i;
		double a2 = get_double_aleatorio(0, 1000);
		hash_table_put(&ht,to_data(&a1,sizeof(long),hp),  to_data(&a2,sizeof(double),hp));
	}
	return ht;
}

void test_hash_table() {
	memory_heap hp = memory_heap_create();
	printf("Hash Table test\n\n");
	hash_table ht = complete_table(&hp);
	hash_table_tostring(&ht,double_tostring);
	printf("\n2:\n");
	long a1 = 31;
	void * e = to_data(&a1,sizeof(long),&hp);
	printf("\n3: contains = %s\n",hash_table_contains(&ht,e)?"true":"false");
	hash_table_remove(&ht,e);
	printf("\n4: contains = %s\n",hash_table_contains(&ht,e)?"true":"false");
	memory_heap_free(&hp);
	hash_table_free(&ht);
}

void test_tree(){
	printf("Binary Tree test\n\n");
	memory_heap hp = memory_heap_create();
	binary_tree_memory_create();
	char mem[500];

	int a = 84; void * pa = to_data(&a,sizeof(int),&hp);
	int b = 90; void * pb = to_data(&b,sizeof(int),&hp);
	int c = 56; void * pc = to_data(&c,sizeof(int),&hp);
	int d = 81; void * pd = to_data(&d,sizeof(int),&hp);
	int e = 55; void * pe = to_data(&e,sizeof(int),&hp);

	binary_tree * t0 = tree_empty();
	binary_tree * t1 = tree_leaf(pc);
	binary_tree * t2 = tree_binary(pa,t0,t1);
	binary_tree * t3 = tree_binary(pb,t2,tree_leaf(pe));
	binary_tree * t4 = tree_binary(pd,t3,t3);
	printf("size = %d\n\n", tree_size(t4));
	alist ls = tree_to_list(t4);
	char * s = alist_tostring(&ls, int_tostring, mem);
	printf("ls = %s\n", s);
	alist_sort(&ls,int_naturalorder);
	s = alist_tostring(&ls, int_tostring, mem);
	printf("ls = %s\n\n", s);
	tree_tostring(t4,int_tostring);
	printf("\n\n");
	memory_heap_free(&hp);
	binary_tree_memory_free();
}

bool pd(void * t){
	time_t e = create_time(1,1,1992);
	return time_naturalorder(t,&e) >0;
}

memory_heap hp;

void * add(void * t){
	time_t e = *(time_t *)t;
	time_t r = time_add_days(e,90);
	return to_data(&r,sizeof(time_t),&hp);
}

void test_dates(){
	hp = memory_heap_create();
	char mem[1000];
	time_t now = now_time();
	time_t t1 = create_time(2,3,1990);
	printf("%s\n",time_tostring(&now,NULL));
	printf("%s\n",time_tostring(&t1,NULL));
	time_t a[] = {
		create_time(2,3,1991),
		create_time(1,5,1995),
		create_time(2,9,1989),
		create_time(2,7,2001),
		create_time(1,1,2019),
		create_time(3,4,2010),
		create_time(1,5,2013),
	};
	alist ls = alist_create(a,7,sizeof(time_t));
	alist_sort(&ls,time_naturalorder);
	char * s=  alist_tostring(&ls,time_tostring,mem);
	printf("1: %s\n",s);
	alist f = alist_filter(&ls,pd);
	s=  alist_tostring(&f,time_tostring,mem);
	printf("2: %s\n",s);
	alist f2 = alist_map(&ls,add);
	s=  alist_tostring(&f2,time_tostring,mem);
	printf("3: %s\n",s);
	memory_heap_free(&hp);

}

int main() {
// test_ejemplos();
//  printf("\n\n\n");
// test_list();
// printf("\n\n\n");
// test_hash_table();
//	test_tree();
test_dates();
}

