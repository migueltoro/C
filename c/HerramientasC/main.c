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
		string_buffer_add(buffer, double_type.tostring(mem, &a1));
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
	tuple2 t1 = {double_type,double_type,&a1,&a2};
	void * pt1 = tuple2_type.pointer(&t1,&heap);
	printf("1: %s\n",tuple2_type.tostring(mem,pt1));
	a1 = getDoubleAleatorio(0, 1000);
	a2 = getDoubleAleatorio(0, 1000);
	tuple2 t2 = {double_type,double_type,&a1,&a2};
	void * pt2 = tuple2_type.pointer(&t2,&heap);
	printf("2: %s\n",tuple2_type.tostring(mem,pt2));
	printf("3: %d\n",tuple2_type.naturalorder(pt1,pt2));
	memory_heap_free(&heap);
}

void test_quicksort(){
	printf("Quicksort test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n");
	memory_heap heap = memory_heap_create();
	int tam = 100;
	type type = instance_type_2(tuple2_type,double_type,double_type);
	tuple2 t = {double_type,double_type,NULL,NULL};
	void ** b = memory_heap_tam_memory(&heap,tam*sizeof(void*));
	for(int i = 0; i<tam; i++) {
		double a1 = getDoubleAleatorio(0, 1000);
		double a2 = getDoubleAleatorio(0, 1000);
		t.key = memory_heap_memory_for_value(&heap,get_parameter_type(type,0).size_type,&a1);
		t.value = memory_heap_memory_for_value(&heap,get_parameter_type(type,1).size_type,&a2);
		void * pt = type.pointer(&t,&heap);
		b[i] = type.pointer(pt,&heap);
	}
	print_array(&buffer,b,0,tam,type);
	generic_qsort(b,0,tam,type.naturalorder);
	printf("\n");
	print_array(&buffer,b,0,tam,type);
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
	list ls = list_empty(double_type);
	for (int i = 0; i < tam; i++) {
		double a = getDoubleAleatorio(0, 1000);
		void * pt = ls.element_type.pointer(&a, &heap);
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
	printf("\n\n%s\n", ls.element_type.tostring(mem, list_get(ls, 20)));
	printf("\nLista\n");
	stream s1 = list_stream_(&ls);
	string_buffer_close(&buffer);
	stream_to_buffer(&buffer, &s1);
	string_buffer_close(&buffer);
	printf("\nLista Map\n");
	s1 = list_stream_(&ls);
	stream s2 = stream_map(&s1, int_type, double_to_int);
	stream_to_buffer(&buffer, &s2);
	string_buffer_close(&buffer);
	printf("\nLista Map Filter\n");
	s1 = list_stream_(&ls);
	s2 = stream_map(&s1, int_type, double_to_int);
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
		void * t1 = int_type.pointer(&a1,&heap);
		double a2 = getDoubleAleatorio(0, 1000);
		void * t2 = double_type.pointer(&a2,&heap);
		hash_table_put(&ht, t1, t2);
	}
	int a = 658;
	void * t3 = int_type.pointer(&a,&heap);
	hash_table_remove(&ht,t3);
	a = 492;
	t3 = int_type.pointer(&a,&heap);
	hash_table_remove(&ht,t3);
	return ht;
}

void test_hash_table() {
	printf("Hash Table test\n\n");
	string_buffer buffer = string_buffer_create("","\n{","}\n");
	memory_heap heap = memory_heap_create();
	hash_table ht = complete_table(heap);
	hash_table_tostring(&buffer,ht);
	string_buffer_free(&buffer);
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
	stream s3 = stream_map(&s2, long_type, square);
	printf("Secuencia de los cuadrados de los primos menores que 300\n\n");
	stream_to_buffer(&buffer, &s3);
}

void test_tree(){
	printf("Binary Tree test\n\n");
	string_buffer buffer = string_buffer_create("","\n","\n\n");
	binary_tree * t0 = tree_empty(int_type);
	binary_tree * t1 = tree_leaf(int_type,get_int_tree(84));
	binary_tree * t2 = tree_binary(get_int_tree(90),t0,t1);
	binary_tree * t3 = tree_binary(get_int_tree(56),t2,tree_leaf(int_type,get_int_tree(55)));
	binary_tree * t4 = tree_binary(get_int_tree(81),t3,t3);
	printf("size = %d\n\n", tree_size(t4));
	tree_to_buffer(&buffer,t4);
	printf("\n\n");
	binary_tree_memory_clear();
}

int main() {
//test_string_buffer();
//test_quicksort();
//test_tuple2();
//test_list();
//test_hash_table();
//test_file_stream();
test_accumulator();
//test_tree();
}

