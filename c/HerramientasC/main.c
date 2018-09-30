/*
 * main.c
 *
 *  Created on: 7 ago. 2018
 *      Author: migueltoro
 */
#include "basic_types.h"
#include "list.h"
#include "string_buffer.h"
#include "memory_heap.h"
#include "stream.h"
#include "new_math.h"
#include "library.h"
#include "hash_table.h"
#include "accumulator.h"
#include "binary_tree.h"
#include "generator.h"
#include "test_generator.h"
#include "ejemplos.h"


bool is_multiple_3(int source){
	return source % 3 ==0;
}



bool gt_300(tuple2 t) {
	return *(double*)t.key >300;
}



int triple_int(int a) {
	return 3*a;
}


void * sqrt_double(void * out, void * in){
	double source = *(double*)in;
	double r = sqrt(abs(source));
	double * p_out = (double *) out;
	(* p_out) = r;
	return p_out;
}


double sqrt_second_double(tuple2 source){
	double r =  *(double*) source.value;
	return  sqrt(r);
}


void * tuple2_value(void * out, void * in){
	tuple2 t = *(tuple2*)in;
	double * p_out = (double *) out;
	(* p_out) = *(double *) t.value;
	return out;
}



void complete_buffer(string_buffer * buffer) {
	char mem[Tam_String];
	int tam = 10;
	string_buffer_add_prefix(buffer);
	for (int i = 0; i < tam; i++) {
		double a1 = getDoubleAleatorio(0, 1000);
		string_buffer_add(buffer,tostring(&double_type,mem, &a1));
	}
	string_buffer_add_sufix(buffer);
	string_buffer_close(buffer);
}

void test_string_buffer(){
	printf("String Buffer test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n");
	complete_buffer(&buffer);
	string_buffer_close(&buffer);
}

void test_tuple2(){
	printf("Tuple2 test\n\n");
	memory_heap heap = memory_heap_create();
	char mem[Tam_String];
	double a1 = getDoubleAleatorio(0, 1000);
	double a2 = getDoubleAleatorio(0, 1000);
	tuple2 v1 = {&a1,&a2};
	type t = instance_type_2(tuple2_type,double_type,double_type);
	void * pt1 = pointer(&t,&v1,&heap);
	printf("1: %s\n",tostring(&t,mem,pt1));
	a1 = getDoubleAleatorio(0, 1000);
	a2 = getDoubleAleatorio(0, 1000);
	tuple2 v2 = {&a1,&a2};
	void * pt2 = pointer(&t,&v2,&heap);
	printf("2: %s\n",tostring(&t,mem,pt2));
	printf("3: %d\n",naturalorder(&t,pt1,pt2));
	memory_heap_free(&heap);
}

void test_quicksort(){
	printf("Quicksort test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n");
	memory_heap heap = memory_heap_create();
	int tam = 100;
	type t = instance_type_2(tuple2_type,double_type,double_type);
	tuple2 v = {NULL,NULL};
	void ** b = memory_heap_tam_memory(&heap,tam*sizeof(void*));
	for(int i = 0; i<tam; i++) {
		double a1 = getDoubleAleatorio(0, 1000);
		double a2 = getDoubleAleatorio(0, 1000);
		v.key = memory_heap_memory_for_value(&heap,get_parameter_type(t,0).size_type,&a1);
		v.value = memory_heap_memory_for_value(&heap,get_parameter_type(t,1).size_type,&a2);
		void * pt = pointer(&t,&v,&heap);
		b[i] = pointer(&t,pt,&heap);
	}
	print_array(&buffer,b,0,tam,&t);
	generic_qsort(b,0,tam,&t);
	printf("\n");
	print_array(&buffer,b,0,tam,&t);
	string_buffer_free(&buffer);
	free(b);
	memory_heap_free(&heap);
}



bool le_200(void * in) {
	double r = *(double*) in;
	return r <= 200;
}

bool int_pair(void * in) {
	int r = *(int*) in;
	return r%2 == 0;
}

void * sqrt_d(void * out, void * in){
	double r = *(double*) in;
	double * p_out = (double *) out;
	(* p_out) = sqrt(r);
	return p_out;
}

void * double_to_int_module_7(void * out, void * in){
	double r = *(double*) in;
	int * p_out = (int *) out;
	(* p_out) = ((int)r) % 7;
	return p_out;
}

void * double_to_int(void * out, void * in) {
	double r = *(double*) in;
	int * p_out = (int *) out;
	(*p_out) = ((int) r);
	return p_out;
}

list complete_list(memory_heap heap) {
	int tam = 30;
	list ls = list_empty(&double_type);
	for (int i = 0; i < tam; i++) {
		double a = getDoubleAleatorio(0, 1000);
		void * pt = pointer(ls.element_type,&a, &heap);
		list_add(&ls, pt);
	}
	return ls;
}

void test_list() {
	printf("List test\n\n");
	char mem[Tam_String];
	string_buffer buffer = string_buffer_create(",", "\n{", "}\n");
	memory_heap heap = memory_heap_create();
	list ls = complete_list(heap);
	print_array(&buffer, ls.elements, 0, ls.size, ls.element_type);
	list_sort_naturalorder(&ls);
	printf("\n\n");
	print_array(&buffer, ls.elements, 0, ls.size, ls.element_type);
	printf("\n\n%s\n", tostring(ls.element_type,mem, list_get(ls, 20)));
	printf("\nLista\n");
	stream s1 = list_stream_(&ls);
	string_buffer_close(&buffer);
	stream_to_buffer(&buffer, &s1);
	string_buffer_close(&buffer);
	printf("\nLista Map\n");
	s1 = list_stream_(&ls);
	stream s2 = stream_map(&s1, &int_type, double_to_int);
	stream_to_buffer(&buffer, &s2);
	string_buffer_close(&buffer);
	printf("\nLista Map Filter\n");
	s1 = list_stream_(&ls);
	s2 = stream_map(&s1, &int_type, double_to_int);
	stream s3 = stream_filter(&s2, int_pair);
	stream_to_buffer(&buffer, &s3);
	string_buffer_close(&buffer);
	memory_heap_free(&heap);
	stream_memory_clear();
}

hash_table complete_table(memory_heap heap) {
	int tam = 500;
	hash_table ht = hash_table_create(int_type, double_type);
	for (int i = 0; i < tam; i++) {
		int a1 = (int)getDoubleAleatorio(0, 1000);
		void * t1 = pointer(&int_type,&a1,&heap);
		double a2 = getDoubleAleatorio(0, 1000);
		void * t2 = pointer(&double_type,&a2,&heap);
		hash_table_put(&ht, t1, t2);
	}
	int a = 658;
	void * t3 = pointer(&int_type,&a,&heap);
	hash_table_remove(&ht,t3);
	a = 492;
	t3 = pointer(&int_type,&a,&heap);
	hash_table_remove(&ht,t3);
	return ht;
}



void test_hash_table() {
	printf("Hash Table test\n\n");
	string_buffer buffer = string_buffer_create("", "\n{", "}\n");
	memory_heap heap = memory_heap_create();
	hash_table ht = complete_table(heap);
	hash_table_tostring(&buffer, &ht);
	string_buffer_close(&buffer);
	printf("\n\nEntradas\n\n");
	hash_table_entries_buffer(&ht,&buffer);
	memory_heap_free(&heap);
	hash_table_free(&ht);
}

void test_file_stream() {
	printf("File Stream test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n");
	stream sf = file_stream("prueba.txt");
	stream_to_buffer(&buffer,&sf);
}

bool lt_500(long a){
	return a < 500;
}

bool ge_300(void * in) {
	long r = *(long*) in;
	return r >= 300;
}

void * square(void * out, void * in){
	long r = *(long*) in;
	long * p_out = (long *) out;
	(* p_out) = r*r;
	return p_out;
}

void test_accumulator() {
	printf("File Stream test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n\n");
	accumulator ac = accumulator_sum_long();
	stream st = stream_range_int(2,100,2);
	stream_to_buffer(&buffer,&st);
	st = stream_range_int(2,100,2);
	long r1 = to_long accumulate_left(&st,&ac);
	st = stream_range_int(2,100,2);
	long r2 = to_long accumulate_right(&st,&ac);
	printf("left = %ld, right = %ld\n\n",r1,r2);
	stream s1 = stream_iterate_long(2, lt_500, siguientePrimo);
	printf("Secuencia de primos menores que 500\n\n");
	stream_to_buffer(&buffer, &s1);
	s1 = stream_iterate_long(2, lt_500, siguientePrimo);
	stream s2 = stream_filter(&s1, ge_300);
	printf("Secuencia de primos mayores que 300 y menores que 500\n\n");
	stream_to_buffer(&buffer, &s2);
	s1 = stream_iterate_long(2, lt_500, siguientePrimo);
	s2 = stream_filter(&s1, ge_300);
	stream s3 = stream_map(&s2, &long_type, square);
	printf("Secuencia de los cuadrados de los primos menores que 300\n\n");
	stream_to_buffer(&buffer, &s3);
}

void test_tree(){
	printf("Binary Tree test\n\n");
	string_buffer buffer = string_buffer_create("","\n","\n\n");
	binary_tree * t0 = tree_empty(&int_type);
	binary_tree * t1 = tree_leaf(&int_type,get_int_tree(84));
	binary_tree * t2 = tree_binary(get_int_tree(90),t0,t1);
	binary_tree * t3 = tree_binary(get_int_tree(56),t2,tree_leaf(&int_type,get_int_tree(55)));
	binary_tree * t4 = tree_binary(get_int_tree(81),t3,t3);
	printf("size = %d\n\n", tree_size(t4));
	tree_to_buffer(&buffer,t4);
	printf("\n\n");
	binary_tree_memory_clear();
}

void test_generator() {
	string_buffer buffer = string_buffer_create(",","{","}\n");
	parameters_test pp = {10,200,5,50,100,5,0,0};
	generator ge = get_generator_test(&pp);
	stream st = generator_stream(&ge);
	stream_to_buffer(&buffer, &st);
}

bool impar(int e){
	return e%2==1;
}

bool impar_y_primo(int e){
	return e%2==1 && es_primo(e);
}

int compare(punto * p1, punto * p2){
	int r;
	if(p1->x > p2->y) r = 1;
	else if (p1->x < p2->y) r = -1;
	else  r = 0;
	return r;
}

void test_ejemplos(){
	double d1[] = {45.,56,90.,1.,23., 78.,76.};
	double_list ls1 = create_double_list(d1,7,7);
	double r1 = problema1(ls1);
	printf("r1 = %lf\n",r1);

	int d3[] = {45,57,10,1,23,77,79};
	int_list ls3 = create_int_list(d3,7,7);
	bool r3 = problema3(ls3,impar);
	printf("r3 = %s\n",r3?"true":"false");

	bool r4 = problema4(ls3,impar_y_primo);
	printf("r4 = %s\n",r4?"true":"false");

	int r5 =  problema5(ls3);
	printf("r5 = %d\n",r5);

	double r6 = problema6(ls1,10.);
	printf("r6 = %lf\n",r6);

	punto ap[] = {{1.,2.},{-1.,2.1},{3.1,2.1},{1.3,27.0},{1.,-2.}};
	punto_list r2 = create_punto_list(ap,5,5);
	double_list s = problema2(r2);
	imprime_list_punto(r2,",","{","}");
	printf("\n");
	imprime_list_double(s,",","{","}");
	printf("\n");

	punto * p = problema8(r2,compare);
	printf("(%.2lf,%.2lf)",p->x,p->y);

	printf("\n\n");

	file_iterator f = open_file("prueba.txt");
	while(has_next_line(&f)){
		printf("%s\n",next_line(&f));
	}
	fclose(f.file);

	printf("\n\n");

	punto_list r7 = list_punto_from_file("prueba.txt");
	imprime_list_punto(r7,",","{","}");
}

int main() {
//test_string_buffer();
//test_quicksort();
//test_tuple2();
//test_list();
//test_hash_table();
//test_file_stream();
//test_accumulator();
//test_tree();
//test_generator();
test_ejemplos();
}

