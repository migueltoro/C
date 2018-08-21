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

EXPAND_RB(is_multiple_3,int,bool);

bool is_first_pair(tuple2_int t) {
	return t.key % 2 ==0;
}

EXPAND_RB(is_first_pair,tuple2_int,bool);


int triple_int(int a) {
	return 3*a;
}

EXPAND(triple_int,int,int);


double sqrt_double(double source){
	double r = sqrt(abs(source));
	return r;
}

EXPAND(sqrt_double,double,double);

double sqrt_second_double(tuple2 source){
	double r =  *(double*) source.value;
	return  sqrt(r);
}

EXPAND(sqrt_second_double,tuple2,double);

void * tuple2_value(tuple2 t){
	return t.value;
}

EXPAND(tuple2_value,tuple2,void *);

void complete_buffer(string_buffer * buffer) {
	char mem[Tam_String];
	int tam = 10;
	for (int i = 0; i < tam; i++) {
		double a1 = getDoubleAleatorio(0, 1000);
		string_buffer_add(buffer, double_type.tostring(mem, &a1));
	}
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
	type type = tuple2_type;
	void ** b = malloc(tam*sizeof(void*));
	for(int i = 0; i<tam; i++) {
		double a1 = getDoubleAleatorio(0, 1000);
		double a2 = getDoubleAleatorio(0, 1000);
		tuple2 t = {double_type,double_type,&a1,&a2};
		void * pt = tuple2_type.pointer(&t,&heap);
		b[i] = tuple2_type.pointer(pt,&heap);
	}
	print_array(&buffer,b,0,tam,type);
	generic_qsort(b,0,tam,type.naturalorder);
	printf("\n");
	print_array(&buffer,b,0,tam,type);
	string_buffer_free(&buffer);
	free(b);
	memory_heap_free(&heap);
}

void test_list_stream() {
	printf("List test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n");
	memory_heap heap = memory_heap_create();
	char mem[Tam_String];
	int tam = 40;
	list ls = list_empty(tuple2_type);
	for (int i = 0; i < tam; i++) {
		double a1 = getDoubleAleatorio(0, 1000);
		double a2 = getDoubleAleatorio(0, 1000);
		tuple2 t = {double_type,double_type,&a1,&a2};
		void * pt = tuple2_type.pointer(&t,&heap);
		list_add(&ls,pt);
	}
	stream st = list_stream(ls);
	stream_to_buffer(&buffer,st);
	list_sort_naturalorder(&ls);
	st = list_stream(ls);
	stream_to_buffer(&buffer,st);
	st = list_stream(ls);
	stream sf = stream_filter(st,__is_first_pair);
	stream sm = stream_map(sf,double_type,__tuple2_value);
	stream ss = stream_map(sm,double_type,__sqrt_double);
	stream_to_buffer(&buffer,ss);
	printf("%s\n",ls.element_type.tostring(mem,list_get(ls,20)));
	string_buffer_free(&buffer);
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
	stream_to_buffer(&buffer,sf);
}

void test_accumulator() {
	printf("File Stream test\n\n");
	string_buffer buffer = string_buffer_create(",","\n{","}\n\n");
	accumulator ac = accumulator_sum_long();
	stream st = stream_range_int(2,100,2);
	stream_to_buffer(&buffer,st);
	st = stream_range_int(2,100,2);
	long r1 = to_long accumulate_left(st,ac);
	st = stream_range_int(2,100,2);
	long r2 = to_long accumulate_right(&st,&ac);
	printf("left = %ld, right = %ld\n\n",r1,r2);
}

void test_tree(){
	printf("Binary Tree test\n\n");
	string_buffer buffer = string_buffer_create("","\n","\n\n");
	binary_tree * t0 = tree_empty(int_type);
	binary_tree * t1 = tree_leaf(get_int_tree(84),int_type);
	binary_tree * t2 = tree_binary(get_int_tree(90),t0,t1);
	binary_tree * t3 = tree_binary(get_int_tree(56),t2,tree_leaf(get_int_tree(55),int_type));
	binary_tree * t4 = tree_binary(get_int_tree(81),t3,t3);
	printf("size = %d\n\n", tree_size(t4));
	tree_to_buffer(&buffer,t4);
	printf("\n\n");
	list * ls = tree_to_list(t4);
	stream st = list_stream(*ls);
	buffer = string_buffer_create(",","{","}\n");
	stream_to_buffer(&buffer,st);

	binary_tree_memory_clear();

}

int main() {
test_string_buffer();
test_quicksort();
test_tuple2();
test_list_stream();
//test_hash_table();
//test_file_stream();
//test_accumulator();
//test_tree();
}

