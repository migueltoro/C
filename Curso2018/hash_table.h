/*
 * hash_table.h
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "types.h"
#include "sorted_list.h"

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
} hash_table;

hash_table hash_table_create(
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e,char * mem));
void * hash_table_put(hash_table * table, void * key, void * value);
void * hash_table_remove(hash_table * table, void * key);
void * hash_table_get(hash_table * table, void * key);
bool hash_table_contains(hash_table * table, void * key);
void hash_table_free(hash_table * table);
void hash_table_tostring(hash_table * table, char * (*tostring_value)(const void * e,char * mem));

#endif /* HASH_TABLE_H_ */
