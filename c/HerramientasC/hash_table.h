/*
 * hash_table.h
 *
 *  Created on: 7 ago. 2018
 *      Author: migueltoro
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "basic_types.h"
#include "memory_heap.h"
#include "string_buffer.h"
#include "generator.h"


typedef struct {
    void * key;
    void * value;
    short next;
} entry_data;

typedef struct {
    int capacity;
    float load_factor_limit;
    int capacity_data;
    int size;
    short first_free_data;
} parameters_hash_table;

typedef struct {
    type key_type;
    type value_type;
    parameters_hash_table parameters;
    entry_data * data;
    int * blocks;
} hash_table;

typedef struct {
	int index_block;
	int index_data;
	hash_table * table;
}hash_table_generator_parameters;

typedef struct {
	entry_data * data;
}hash_table_generator_values;

hash_table hash_table_create(type,type);
string_buffer * hash_table_tostring(string_buffer * buffer, hash_table * table);
void * hash_table_put(hash_table * table, void * key, void * value);
void * hash_table_remove(hash_table * table, void * key);
void * hash_table_get(hash_table * table, void * key);
tuple2 * hash_table_get_entry(hash_table * table, void * key);
int hash_table_contains(hash_table * table, void * key);
generator hash_table_generator(hash_table_generator_parameters * p);
void hash_table_entries_buffer(hash_table * table, string_buffer * buffer);
void hash_table_free(hash_table * table);

extern type hash_table_type;

//extern parameters_hash_table initial_parameters;

#endif /* HASH_TABLE_H_ */
