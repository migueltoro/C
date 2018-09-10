/*
 * basic_types.h
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */

#ifndef BASIC_TYPES_H_
#define BASIC_TYPES_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "definitions.h"
#include "memory_heap.h"

typedef struct tt {
	int num_type_parameters;
	struct tt * types;
    int size_type;
    char * (*tostring)(struct tt *,char *, const void *);
    int (*equals)(struct tt *, const void *, const void *);
    long (*hashcode) (struct tt *, const void *);
    int (*naturalorder) (struct tt *, const void *, const void *);
    void * (*pointer)(struct tt *, const void * value, memory_heap * heap);
    void * (*copy) (struct tt *, void * target, const void * source);
    char * id;
} type;

unsigned long int hash(const char * key);
int type_equals(type * t1, type * t2);
type instance_type_1(type generic_type, type t1);
type instance_type_2(type generic_type, type t1, type t2);
type get_parameter_type(type generic_type, int index);

char * tostring(type *, char * mem, const void * e);
long hashcode(type *, const void * e);
int equals(type *, const void * e1, const void * e2);
int naturalorder(type *, const void * e1, const void * e2);
void * pointer(type *, const void * value, memory_heap * heap);
void * copy(type *, void * target, const void * source);

// data type

typedef struct {
	void * value;
	type type;
}data;


char * data_tostring(char * mem, const void * e);
long data_hashcode(const void * e);
int data_equals(const void * e1, const void * e2);
int data_naturalorder(const void * e1, const void * e2);
void * data_pointer(const void * value, memory_heap * heap);
void * data_copy(void * target, const void * source);

extern type data_type;

// int type

char * int_tostring(type *, char * mem, const void * e);
long int_hashcode(type *, const void * e);
int int_equals(type *, const void * e1, const void * e2);
int int_naturalorder(type *, const void * e1, const void * e2);
void * int_pointer(type *, const void * value, memory_heap * heap);
void * int_copy(type *, void * target, const void * source);
void  * int_pointer_from_value(int a, memory_heap * heap);



extern type int_type;

// long type
char * long_tostring(type *, char * mem, const void * e);
long long_hashcode(type *, const void * e);
int long_equals(type *, const void * e1, const void * e2);
int long_naturalorder(type *, const void * e1, const void * e2);
void * long_pointer(type *, const void * value, memory_heap * heap);
void * long_copy(type *, void * target, const void * source);
void  * long_pointer_from_value(long a, memory_heap * heap);

extern type long_type;

// float type

char * float_tostring(type *, char * mem, const void * e);
long float_hashcode(type *, const void * e);
int float_equals(type *, const void * e1, const void * e2);
int float_naturalorder(type *, const void * e1,const  void * e2);
void * float_pointer(type *, const void * value, memory_heap * heap);
void * float_copy(type *, void * target, const void * source);
void  * float_pointer_from_value(type *, float a,memory_heap * heap);



extern type float_type;

// double type

char * double_tostring(type *, char * mem, const void * e);
long double_hashcode(type *, const void * e);
int double_equals(type *, const void * e1, const void * e2);
int double_naturalorder(type *, const void * e1,const  void * e2);
void * double_pointer(type *, const void * value, memory_heap * heap);
void * double_copy(type *, void * target, const void * source);
void  * double_pointer_from_value(type *, double a, memory_heap * heap);


extern type double_type;

// string type

#define Tam_String 256

char * string_tostring(type *, char * mem, const void * e);
long string_hashcode(type *, const void * e);
int string_equals(type *, const void * e1, const void * e2);
int string_naturalorder(type *, const void * e1,const  void * e2);
void * string_pointer(type *, const void * value, memory_heap * heap);
void * string_copy(type *, void * target, const void * source);


char * remove_eol(char * string);

extern type string_type;

// tuple2 type

typedef struct {
	 void * key;
	 void * value;
} tuple2;


char * tuple2_tostring(type *, char * mem, const void * t);
int tuple2_equals(type *, const void * t1, const void * t2);
long tuple2_hashcode(type *, const void * t);
int tuple2_naturalorder(type *, const void * t1,const  void * t2);
void * tuple2_pointer(type *,const void * value, memory_heap * heap);
void * tuple2_copy(type *, void * target, const void * source);


extern type tuple2_type;

// optional type

typedef struct {
	 void * value;
} optional;

char * optional_tostring(type *, char * mem, const void * t);
int optional_equals(type *, const void * t1, const void * t2);
long optional_hashcode(type *, const void * t);
int optional_naturalorder(type *, const void * t1,const  void * t2);
void * optional_pointer(type *, const void * value, memory_heap * heap);
void * optional_copy(type *, void * target, const void * source);

extern type optional_type;

// void * type

extern type void_star_type;

// unkown type

extern type unkown_type;

typedef struct {
	double x;
	double y;
} punto;


typedef enum {PRIMERO,SEGUNDO,TERCERO,CUARTO} Cuadrante;


double punto_distancia_al_origen(const punto p);
int punto_ord_distancia_al_origen(const punto p1, const punto p2);

Cuadrante punto_cuadrante(const punto p);

char * punto_tostring(type *, char * mem, const void * p);
int punto_equals(type *, const void * p1, const void * p2);
long punto_hashcode(type *, const void * p);
int punto_naturalorder(type *, const void * t1,const  void * t2);
void * punto_pointer(type *, const void * value, memory_heap * heap);
void * punto_copy(type *, void * target, const void * source);

extern type punto_type;



void types_memory_clear();

#endif /* BASIC_TYPES_H_ */
