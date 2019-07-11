/*
 * types.h
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <float.h>

#include "../types/math2.h"
;
unsigned long int hash(const char * key);

typedef struct{
	bool (* equals)(const void * e1, const void * e2);
	char * (* tostring)(const void * e, char * mem);
	int (* order)(const void * e1, const void * e2);
	void * (* copy)(void * out, void * in);
	void * (*pointer_copy)(void * out, void * in);
	void * (*parse)(void * out, char * text);
	int size;
}type;

// int type

int int_parse(char * text);
void * int_parse_g(void * out, char * text);
char * int_tostring(const void * e, char * mem);
bool int_equals(const void * e1, const void * e2);
int int_naturalorder(const void * e1, const void * e2);
int to_int(void * in);
int * to_int_pointer(void * in);
void * int_copy(void * out, void * in);
void * int_pointer_copy(void * out, void * in);

extern type int_type;

#define bool_tostring(b) b?"true":"false"

// long type

long long_parse(char * text);
void * long_parse_g(void * out, char * text);
char * long_tostring(const void * e, char * mem);
bool long_equals(const void * e1, const void * e2);
int long_naturalorder(const void * e1, const void * e2);
long to_long(void * in);
long * to_long_pointer(void * in);
void * long_copy(void * out, void * in);
void * long_pointer_copy(void * out, void * in);

extern type long_type;

// float type

float float_parse(char * text);
void * float_parse_g(void * out, char * text);
char * float_tostring(const void * e, char * mem);
bool float_equals(const void * e1, const void * e2);
int float_naturalorder(const void * e1,const  void * e2);
float to_float(void * in);
float * to_float_pointer(void * in);
void * float_copy(void * out, void * in);
void * float_pointer_copy(void * out, void * in);

extern type int_type;

// double type

double double_parse(char * text);
void * double_parse_g(void * out, char * text);
char * double_tostring(const void * e, char * mem);
bool double_equals(const void * e1, const void * e2);
int double_naturalorder(const void * e1,const  void * e2);
double to_double(void * in);
double * to_double_pointer(void * in);
void * double_copy(void * out, void * in);
void * double_pointer_copy(void * out, void * in);

extern type double_type;

// int_pair

typedef struct{
	int a;
	int b;
}int_pair;

int_pair int_pair_parse(char * text);
void * int_pair_parse_g(void * out, char * text);
char * int_pair_tostring(const void * t, char * mem);
bool int_pair_equals(const void * t1, const void * t2);
int int_pair_naturalorder(const void * t1,const  void * t2);
int_pair to_int_pair(void * in);
int_pair * to_int_pair_pointer(void * in);
void * int_pair_copy(void * out, void * in);
void * int_pair_pointer_copy(void * out, void * in);

extern type int_pair_type;

// punto

typedef struct {
	double x;
	double y;
} punto;


typedef enum {PRIMERO,SEGUNDO,TERCERO,CUARTO} Cuadrante;


double punto_distancia_al_origen(const punto p);
int punto_ord_distancia_al_origen(const punto p1, const punto p2);


Cuadrante punto_cuadrante(const punto p);

punto punto_parse(char * text);
void * punto_parse_g(void * out, char * text);
char * punto_tostring(const void * p, char * mem);
bool punto_equals(const void * p1, const void * p2);
int punto_naturalorder(const void * t1,const  void * t2);
punto to_punto(void * in);
punto * to_punto_pointer(void * in);
void * punto_copy(void * out, void * in);
void * punto_pointer_copy(void * out, void * in);

extern type punto_type;

// pair type

typedef struct {
	void * key;
	void * value;
} pair;

typedef struct {
	void * key;
	void * value;
	type * key_type;
	type * value_type;
} pair_t;

void * pair_parse_g(void * out, char * text);
char * pair_tostring(const void * e, char * mem);
bool pair_equals(const void * e1, const void * e2);
int pair_naturalorder(const void * e1, const void * e2);
pair_t to_pair(void * in);
pair_t * to_pair_pointer(void * in);
void * pair_copy(void * out, void * in);
void * pair_pointer_copy(void * out, void * in);

pair_t pair_of(pair p, type * t1, type * t2);
pair_t pair_of_2(void * key, void * value, type * t1, type * t2);

extern type pair_type;

// string type

#define Tam_String 256

typedef char string[Tam_String];

void * string_parse_g(void * out, char * text);
char * string_tostring(const void * e, char * mem);
bool string_equals(const void * e1, const void * e2);
int string_naturalorder(const void * e1,const  void * e2);
char * to_string(void * in);
void * string_copy(void * out, void * in);
void * string_pointer_copy(void * out, void * in);

extern type string_type;

char * remove_eol(char * string);

char ** split(char * text, const char * delimiters, char ** tokens, int * ntokens);

// optional type

typedef struct {
	void * value;
	type * type;
} optional;

void * optional_parse_g(void * out, char * text);
char * optional_tostring(const void * e, char * mem);
bool optional_equals(const void * e1, const void * e2);
int optional_naturalorder(const void * e1, const void * e2);
optional to_optional(void * in);
optional * to_optional_pointer(void * in);
void * optional_copy(void * out, void * in);
void * optional_pointer_copy(void * out, void * in);

optional optional_of(void * in, type * type);
bool is_present(optional * in);

extern type optional_type;

// void * type

extern type void_star_type;

// none type

extern type none_type;

// utilities

void * copy(void * out, void * in, int size);
void * swap(void * out, void * in, int size);

void test_string();
void test_types();

//definitions



#endif /* TYPES_H_ */
