/*
 * hash_table.c
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#include "hash_table.h"

int _primes[] = {13, 23, 41, 61, 83, 151, 199, 263, 383, 503, 641, 769, 911, 1049, 1559};
int _next_prime = 0;
int _nprimes = 15;


int get_index_block(hash_table * table, void * key);
int find_data_entry(hash_table * table, int index_block, void * key);
void ini_data(hash_table * table);
int rehash(hash_table * table);
void * hash_table_put_private(hash_table * table, void * key, void * value);

hash_table hash_table_create(//int key_size, int value_size,
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem)){
	hash_table t;
	t.equals_key = equals;
	t.tostring_key = tostring;
	t.load_factor_limit = 0.75;
	int capacity_blocks = _primes[_next_prime];
	t.capacity_blocks = capacity_blocks;
	t.capacity_data = (int) (0.75* capacity_blocks + 1);
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
	char mem[256];
	table->tostring_key(key, mem);
	unsigned long int hash_index = hash(mem);
	int index = (int) (hash_index % (table->capacity_blocks));
	assert(index >= 0 && index < table->capacity_blocks && "no es el índice de un bloque posible");
	return index;
}

int find_data_entry(hash_table * table, int index_block, void * key) {
	int r = -1;
	int next = table->blocks[index_block];
	while (next >= 0) {
		if (table->equals_key(key,table->data[next].key)) {
			r = next;
			break;
		}
		next = table->data[next].next;
	}
	return r;
}

void * hash_table_put(hash_table * table, void * key, void * value){
	rehash(table);
	return hash_table_put_private(table,key,value);
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


bool hash_table_contains(hash_table * table, void * key){
	int index = get_index_block(table,key);
		int pos = find_data_entry(table,index,key);
		bool r = false;
		if(pos >=0){
			r = true;
		}
		return r;
}

int rehash(hash_table * table) {
	if (table->size < table->capacity_data) return 0;
	_next_prime = _next_prime + 1;
	assert(_next_prime < _nprimes && "se ha acabado los números primos disponibles");
	int old_capacity_blocks = table->capacity_blocks;
	int old_capacity_data = table->capacity_data;
	int * old_blocks = table->blocks;
	entry * old_data = table->data;
	int capacity_blocks = _primes[_next_prime];
	table->capacity_blocks = capacity_blocks;
	table->capacity_data = (int) (0.75* capacity_blocks + 1);
	ini_data(table);
	for (int i = 0; i < old_capacity_blocks; i++) {
		assert( i < old_capacity_blocks && "el índice no está en rango de los bloques disponibles");
		int first = old_blocks[i];
		if (first < 0) continue;
		int j = first;
		while (j >= 0) {
			assert(j < old_capacity_data && "el índice no está en el rango del array de datos");
			hash_table_put_private(table, old_data[j].key, old_data[j].value);
			j = old_data[j].next;
		}
	}
	free(old_blocks);
	free(old_data);
	return 1;
}

void * hash_table_put_private(hash_table * table, void * key, void * value) {
	int index = get_index_block(table, key);
	int pos = find_data_entry(table, index, key);
	if (pos >= 0) {
		table->data[pos].value = value;
	} else {
		int first_free = table->first_free_data;
		table->first_free_data = table->data[first_free].next;
		table->size = table->size + 1;
		table->data[first_free].key = key;
		table->data[first_free].value = value;
		if (table->blocks[index] < 0) {
			table->data[first_free].next = -1;
		} else {
			table->data[first_free].next = table->blocks[index];
		}
		table->blocks[index] = first_free;
	}
	return key;
}

void * hash_table_remove(hash_table * table, void * key) {
	int index = get_index_block(table, key);
	int pos = find_data_entry(table,index,key);
	if (pos >= 0) {
		if(table->blocks[index]==pos){
			table->blocks[index] = table->data[pos].next;
		} else{
			int i = table->blocks[index];
			while(table->data[i].next != pos){
				i = table->data[i].next;
			}
			table->data[i].next = table->data[pos].next;
		}
		table->size = table->size -1;
		table->data[pos].next = table->first_free_data;
		table->first_free_data = pos;
	}
	return key;
}

void hash_table_tostring(hash_table * table, char * (*tostring_value)(const void * e,char * mem)){
	printf("\n");
	char mdata[500];
	char mkey[256];
	char mvalue[256];
	int i,j;
	int blocks_not_empty = 0;
	for(i = 0; i < table->capacity_blocks; i++){
		int first = table->blocks[i];
		if(first < 0) continue;
		blocks_not_empty++;
		j = first;
		sprintf(mdata,"%d: ",i);
		printf("%s",mdata);
		printf("[");
		while(j>=0) {
			void * key = table->data[j].key;
			void * value = 	table->data[j].value;
			sprintf(mdata,"(%s,%s)",table->tostring_key(key,mkey),tostring_value(value,mvalue));
			printf("%s",mdata);
			j = table->data[j].next;
		}
		printf("]\n");
	}
	printf("}");
	sprintf(mdata,"  Effective load factor = %f, capacity: %d, size: %d",
			table->size/((double)blocks_not_empty),
			table->capacity_blocks,
			table->size
			);
	printf("%s",mdata);
}

void hash_table_free(hash_table * table){
	free(table->blocks);
	free(table->data);
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
