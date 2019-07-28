/*
 * hash_table.c
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#include "../types/hash_table.h"

int _primes[] = {13, 23, 41, 61, 83, 151, 199, 263, 383, 503, 641, 769, 911, 1049, 1559, 1709, 2069,5923,11587,56527};
int _next_prime = 0;
int _nprimes = 20;


int get_index_block(hash_table * table, void * key);
int find_data_entry(hash_table * table, int index_block, void * key);
void ini_data(hash_table * table);
int rehash(hash_table * table);
void * hash_table_put_private(hash_table * table, void * key, void * value);

hash_table hash_table_empty(type key_type, type value_type){
	hash_table t;
	t.key_type = key_type;
	t.value_type = value_type;
	t.load_factor_limit = 0.75;
	int capacity_blocks = _primes[_next_prime];
	t.capacity_blocks = capacity_blocks;
	t.capacity_data = (int) (t.load_factor_limit* capacity_blocks + 1);
	t.hp = memory_heap_create();
	ini_data(&t);
	return t;
}

void ini_data(hash_table * table) {
	table->blocks = (int *) malloc(table->capacity_blocks*sizeof(int));
	table->data = (entry *) malloc(table->capacity_data*sizeof(entry));
	table->size = 0;
	table->first_free_data = 0;
	for (int i = 0; i < table->capacity_blocks; i++) {
		table->blocks[i] = -1;
	}
	for (int i = 0; i < table->capacity_data; i++) {
		table->data[i].next = i+1;
	}
	table->data[table->capacity_data-1].next = -1;
}

int get_index_block(hash_table * table, void * key) {
	unsigned long int hash_index = hash_code(key,table->key_type);
	int index = (int) (hash_index % (table->capacity_blocks));
	return index;
}

int find_data_entry(hash_table * table, int index_block, void * key) {
	int r = -1;
	int next = table->blocks[index_block];
	while (next >= 0) {
		if (table->key_type.equals(key,table->data[next].key)) {
			r = next;
			break;
		}
		next = table->data[next].next;
	}
	return r;
}

int hash_table_size(hash_table * table){
	return table->size;
}

void * hash_table_put_pointer(hash_table * table, void * key, void * value){
	rehash(table);
	return hash_table_put_private(table,key,value);
}

void * hash_table_put(hash_table * table, void * key, void * value){
	void * k = memory_heap_copy_and_mem(&(table->hp),key,table->key_type.size);
    void * v = memory_heap_copy_and_mem(&(table->hp),value,table->value_type.size);
    return hash_table_put_pointer(table,k,v);
}

void * hash_table_get(hash_table * table, void * key){
	int index = get_index_block(table,key);
	int pos = find_data_entry(table,index,key);
	void * r = NULL;
	if(pos >=0){
		r = table->data[pos].value;
	}
	return r;
}


bool hash_table_contains(hash_table * table, void * key) {
	int index = get_index_block(table, key);
	int pos = find_data_entry(table, index, key);
	bool r = false;
	if (pos >= 0) {
		r = true;
	}
	return r;
}

int rehash(hash_table * table) {
	if (table->size < table->capacity_data) return 0;
	_next_prime = _next_prime + 1;
	check_argument(_next_prime < _nprimes,__FILE__,__LINE__,"se ha acabado los números primos disponibles");
	int old_capacity_blocks = table->capacity_blocks;
	int old_capacity_data = table->capacity_data;
	int * old_blocks = table->blocks;
	entry * old_data = table->data;
	int capacity_blocks = _primes[_next_prime];
	table->capacity_blocks = capacity_blocks;
	table->capacity_data = (int) (0.75* capacity_blocks + 1);
	ini_data(table);
	for (int i = 0; i < old_capacity_blocks; i++) {
		check_argument( i < old_capacity_blocks,__FILE__,__LINE__,"el índice no está en rango de los bloques disponibles");
		int first = old_blocks[i];
		if (first < 0) continue;
		int j = first;
		while (j >= 0) {
			check_argument(j < old_capacity_data,__FILE__,__LINE__,"el índice no está en el rango del array de datos");
			hash_table_put_private(table, old_data[j].key, old_data[j].value);
			j = old_data[j].next;
		}
	}
	free(old_blocks);
	free(old_data);
	return 1;
}

entry * ocupa_primera_libre(hash_table * table, int index) {
	int first_free = table->first_free_data;
	table->first_free_data = table->data[first_free].next;
	if (table->blocks[index] < 0) {
		table->data[first_free].next = -1;
	} else {
		table->data[first_free].next = table->blocks[index];
	}
	table->blocks[index] = first_free;
	return table->data+first_free;
}

void libera(hash_table * table, int index, int index_data) {
	if (table->blocks[index] == index_data) {
		table->blocks[index] = table->data[index_data].next;
	} else {
		int i = table->blocks[index];
		while (table->data[i].next != index_data) {
			i = table->data[i].next;
		}
		table->data[i].next = table->data[index_data].next;
	}
	table->data[index_data].next = table->first_free_data;
	table->first_free_data = index_data;
}

void * hash_table_put_private(hash_table * table, void * key, void * value) {
	int index = get_index_block(table, key);
	int pos = find_data_entry(table, index, key);
	if (pos >= 0) {
		table->data[pos].value = value;
	} else {
		table->size = table->size + 1;
		entry * e = ocupa_primera_libre(table,index);
		e->key = key;
		e->value = value;
	}
	return key;
}

void * hash_table_remove(hash_table * table, void * key) {
	int index = get_index_block(table, key);
	int index_data = find_data_entry(table,index,key);
	if (index_data >= 0) {
		table->size = table->size - 1;
		libera(table, index, index_data);
	}
	return key;
}

typedef struct{
	hash_table * ht;
	int nb;
	int i;
	int j;
//	bool first;
}dependencies_hash_table;

bool iterable_hash_table_has_next(iterator * current_iterable) {
	dependencies_hash_table * dp = (dependencies_hash_table *) current_iterable->dependencies;
	return dp->i < dp->nb;
}

void * iterable_hash_table_see_next(iterator * current_iterable){
	dependencies_hash_table * dp = (dependencies_hash_table *) current_iterable->dependencies;
	hash_table * table = dp->ht;
	pair * state = (pair *)current_iterable->state;
	state->key = table->data[dp->j].key;
	state->value = table->data[dp->j].value;
    return current_iterable->state;
}

void next_state(dependencies_hash_table * dp){
	hash_table * table = dp->ht;
	int i = dp->i;
	int j = dp->j;
	while(i<dp->nb){
		if(j<0) j = table->blocks[i];
		else j = table->data[j].next;
		if(j>=0) break;
		i++;
	}
	dp->i = i;
	dp->j = j;
}

void * iterable_hash_table_next(iterator * current_iterable){
	dependencies_hash_table * dp = (dependencies_hash_table *) current_iterable->dependencies;
	hash_table * table = dp->ht;
	pair * state = (pair *)current_iterable->state;
	state->key = table->data[dp->j].key;
	state->value = table->data[dp->j].value;
	next_state(dp);
	return current_iterable->state;
}

iterator hash_table_items_iterable(hash_table * ht){
	dependencies_hash_table dh = {ht,ht->capacity_blocks,0,-1};
	int size_dh = sizeof(dependencies_hash_table);
	iterator s_hash_table = iterable_create(sizeof(pair),iterable_hash_table_has_next,iterable_hash_table_next,iterable_hash_table_see_next,NULL,&dh,size_dh);
	next_state(s_hash_table.dependencies);
	return s_hash_table;
}

char * hash_table_tostring(hash_table * table, char * mem) {
	char m1[Tam_String];
	char m2[Tam_String];
	char m[Tam_String];
	bool first = true;
	strcpy(mem, "{");
	iterator st = hash_table_items_iterable(table);
	while (iterable_has_next(&st)) {
		pair * next = (pair *) iterable_next(&st);
		char * k = table->key_type.tostring(next->key,m1);
		char * v = table->value_type.tostring(next->value,m2);
		sprintf(m,"(%s,%s)",k,v);
		if (first) {
			first = false;
			strcat(mem, m);
		} else {
			strcat(mem, ",");
			strcat(mem, m);
		}
	}
	strcat(mem, "}");
	return mem;
}

void hash_table_toconsole(hash_table * table, char * (*tostring_value)(const void * e,char * mem)){
	printf("\n");
	char mdata[500];
	char mkey[256];
	char mvalue[256];
	int i,j;
	int blocks_not_empty = 0;
	for(i = 0; i < table->capacity_blocks; i++){
		int first = table->blocks[i];
		if(first < 0) continue;
		j = first;
		sprintf(mdata,"%d: ",i);
		blocks_not_empty++;
		printf("%s",mdata);
		printf("[");
		while(j>=0) {
			void * key = table->data[j].key;
			void * value = 	table->data[j].value;
			sprintf(mdata,"(%s,%s)",table->key_type.tostring(key,mkey),tostring_value(value,mvalue));
			printf("%s",mdata);
			j = table->data[j].next;
		}
		printf("]\n");
	}
	printf("}");
	sprintf(mdata,"  Effective load factor = %f, blocks_not_empty = %d, capacity: %d, size: %d",
			table->size/((double)blocks_not_empty),
			blocks_not_empty,
			table->capacity_blocks,
			table->size
			);
	printf("%s",mdata);
}

void hash_table_free(hash_table * table){
	free(table->blocks);
	free(table->data);
}

void hash_table_free_2(hash_table * table, void (*f_key)(void * in), void (*f_value)(void * in)){
	for(int i =0; i < table->capacity_data; i++){
		entry e = table->data[i];
		f_key(e.key);
		f_value(e.value);
	}
	hash_table_free(table);
}


hash_table complete_table() {
	int tam = 100;
	hash_table ht = hash_table_empty(long_type,double_type);
	new_rand();
	for (int i = 0; i < tam; i++) {
		long a1 = i;
		double a2 = get_double_aleatorio(0, 1000);
		hash_table_put(&ht,&a1,&a2);
	}
	for (int i = 3; i < tam; i++) {
		long a1 = i;
		double a2 = get_double_aleatorio(0, 1000);
		hash_table_put(&ht,&a1,&a2);
	}
	long a1 = 5;
	hash_table_remove(&ht,&a1);
	return ht;
}

bool multiplo_7(long * in){
	return (*in)%7 == 0;
}

char * pair_long_double(const pair * in, char * mem){
	char m1[Tam_String];
	char m2[Tam_String];
	sprintf(mem,"(%s,%s)",long_tostring(in->key,m1),double_tostring(in->value,m2));
	return mem;
}

char * pair_key_long(const pair * in, char * mem){
	char m[Tam_String];
	sprintf(mem,"%s",long_tostring(in->key,m));
	return mem;
}



void test_hash_table() {
	char mem[2000];
	printf("Hash Table test\n\n");
//	printf("2:\n");
	hash_table ht = complete_table();
//	hash_table_toconsole(&ht,double_tostring);
//	long a1 = 31;
//	bool r = hash_table_contains(&ht,&a1);
//	printf("\n3: contains = %s\n",bool_tostring(r));
//	hash_table_remove(&ht,&a1);
//	r = hash_table_contains(&ht,&a1);
//	printf("\n4: contains = %s\n",bool_tostring(r));
//	printf("\n5: \n");
//	hash_table_toconsole(&ht,double_tostring);
//	printf("\n\n\n");
	iterator iht = hash_table_items_iterable(&ht);
	printf("\n6: \n");
	iterable_toconsole_sep(&iht,pair_long_double,",","{","}\n");
	iht = hash_table_items_iterable(&ht);
	printf("\n7: \n");
	iterable_toconsole_sep(&iht,pair_key_long,",","{","}\n");
	printf("\n8: \n");
	printf(hash_table_tostring(&ht,mem));
//	long k = 99;
//	void * r4 = hash_table_get(&ht,&k);
//	optional or4 = optional_of(r4,&double_type);
//	printf("%ld,%s\n",k,optional_type.tostring(&or4,mem));
//	hash_table_remove(&ht,&k);
//	r4 = hash_table_get(&ht,&k);
//	or4 = optional_of(r4,&double_type);
//	printf("%ld,%s\n",k,optional_type.tostring(&or4,mem));
//	printf("__________________\n");
//	dependencies_hash_table dp = {&ht,ht.capacity_blocks,0,-1,true};
//	next_state(&dp);
//	int ss = 0;
//	while(dp.i < dp.nb){
//		ss=ss+1;
////		printf("%d,%d\n",dp.i,dp.j);
//		printf("(%ld,%lf),",*(long*)ht.data[dp.j].key,*(double*)ht.data[dp.j].value);
//		next_state(&dp);
//	}
//	printf("\n%d,%d\n",ss,ht.size);
}

