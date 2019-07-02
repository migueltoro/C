/*
 * hash_table.h
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "list.h"
#include "types.h"
#include "memory_heap.h"

typedef struct {
	void * key;
	void * value;
	int next;
} entry;

typedef struct {
	int (*equals_key)(const void *, const void *);
	char * (*tostring_key)(const void * e,char * mem);
    int * blocks;
	entry * data;
	int size;
	int capacity_blocks;
	int capacity_data;
	int first_free_data;
	float load_factor_limit;
	memory_heap hp;
} hash_table;

hash_table hash_table_empty(
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem));
int hash_table_size(hash_table * table);
void * hash_table_put_pointer(hash_table * table, void * key, void * value);
void * hash_table_put(hash_table * table, void * key, void * value, int size_key, int size_value);
void * hash_table_remove(hash_table * table, void * key);
void * hash_table_get(hash_table * table, void * key);
bool hash_table_contains(hash_table * table, void * key);

void hash_table_free(hash_table * table);
void hash_table_toconsole(hash_table * table, char * (*tostring_value)(const void * e,char * mem));
void test_hash_table();
#endif /* HASH_TABLE_H_ */
