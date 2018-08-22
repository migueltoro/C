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

hash_table hash_table_create(type,type);
string_buffer * hash_table_tostring(string_buffer * buffer, hash_table table);
void * hash_table_put(hash_table * table, void * key, void * value);
void * hash_table_remove(hash_table * table, void * key);
void * hash_table_get(hash_table table, void * key);
int hash_table_contains(hash_table table, void * key);
void hash_table_free(hash_table * table);

extern type hash_table_type;

//extern parameters_hash_table initial_parameters;

#endif /* HASH_TABLE_H_ */
