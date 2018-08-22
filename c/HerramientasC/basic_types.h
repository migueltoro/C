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
    char * (*tostring)(char *, const void *);
    int (*equals)(const void *, const void *);
    long (*hashcode) (const void *);
    int (*naturalorder) (const void *, const void *);
    void * (*pointer)(const void * value, memory_heap * heap);
    void * (*copy) (void * target, const void * source);
    char * id;
} type;

unsigned long int hash(const char *key);
int type_equals(const type t1, const type t2);
type instance_type_1(type generic_type, type t1);
type instance_type_2(type generic_type, type t1, type t2);
type get_parameter_type(type generic_type, int index);

// int type

char * int_tostring(char * mem, const void * e);
long int_hashcode(const void * e);
int int_equals(const void * e1, const void * e2);
int int_naturalorder(const void * e1, const void * e2);
void * int_pointer(const void * value, memory_heap * heap);
void * int_copy(void * target, const void * source);
void  * int_pointer_from_value(int a, memory_heap * heap);



extern type int_type;

// long type
char * long_tostring(char * mem, const void * e);
long long_hashcode(const void * e);
int long_equals(const void * e1, const void * e2);
int long_naturalorder(const void * e1, const void * e2);
void * long_pointer(const void * value, memory_heap * heap);
void * long_copy(void * target, const void * source);
void  * long_pointer_from_value(long a, memory_heap * heap);

extern type long_type;

// float type

char * float_tostring(char * mem, const void * e);
long float_hashcode(const void * e);
int float_equals(const void * e1, const void * e2);
int float_naturalorder(const void * e1,const  void * e2);
void * float_pointer(const void * value, memory_heap * heap);
void * float_copy(void * target, const void * source);
void  * float_pointer_from_value(float a,memory_heap * heap);



extern type float_type;

// double type

char * double_tostring(char * mem, const void * e);
long double_hashcode(const void * e);
int double_equals(const void * e1, const void * e2);
int double_naturalorder(const void * e1,const  void * e2);
void * double_pointer(const void * value, memory_heap * heap);
void * double_copy(void * target, const void * source);
void  * double_pointer_from_value(double a, memory_heap * heap);


extern type double_type;

// string type

#define Tam_String 256

char * string_tostring(char * mem, const void * e);
long string_hashcode(const void * e);
int string_equals(const void * e1, const void * e2);
int string_naturalorder(const void * e1,const  void * e2);
void * string_pointer(const void * value, memory_heap * heap);
void * string_copy(void * target, const void * source);


char * remove_eol(char * string);

extern type string_type;

// tuple2 type

typedef struct {
	 type key_type;
	 type value_type;
	 void * key;
	 void * value;
} tuple2;


char * tuple2_tostring(char * mem, const void * t);
int tuple2_equals(const void * t1, const void * t2);
long tuple2_hashcode(const void * t);
int tuple2_naturalorder(const void * t1,const  void * t2);
void * tuple2_pointer(const void * value, memory_heap * heap);
void * tuple2_copy(void * target, const void * source);


extern type tuple2_type;

// optional type

typedef struct {
	 type type;
	 void * value;
} optional;

char * optional_tostring(char * mem, const void * t);
int optional_equals(const void * t1, const void * t2);
long optional_hashcode(const void * t);
int optional_naturalorder(const void * t1,const  void * t2);
void * optional_pointer(const void * value, memory_heap * heap);
void * optional_copy(void * target, const void * source);

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

char * punto_tostring(char * mem, const void * p);
int punto_equals(const void * p1, const void * p2);
long punto_hashcode(const void * p);
int punto_naturalorder(const void * t1,const  void * t2);
void * punto_pointer(const void * value, memory_heap * heap);
void * punto_copy(void * target, const void * source);

extern type punto_type;

void types_memory_clear();

#endif /* BASIC_TYPES_H_ */
