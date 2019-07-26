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
#include <ctype.h>

#include "../types/math2.h"
#include "../types/preconditions.h"


typedef struct{
	bool (* equals)(const void * e1, const void * e2);
	char * (* tostring)(const void * e, char * mem);
	int (* order)(const void * e1, const void * e2);
	void * (*parse)(void * out, char * text);
	int size;
}type;

unsigned long int hash(const char * key);
unsigned long int hash_code(void * in, type t);

// int type

int int_parse_s(char * text);
int * int_parse(int * out, char * text);
char * int_tostring(const int * e, char * mem);
bool int_equals(const int * e1, const int * e2);
int int_naturalorder(const int * e1, const int * e2);

extern type int_type;

#define bool_tostring(b) b?"true":"false"

// long type

long long_parse_s(char * text);
long * long_parse(long * out, char * text);
char * long_tostring(const long * e, char * mem);
bool long_equals(const long * e1, const long * e2);
int long_naturalorder(const long * e1, const long * e2);

extern type long_type;

// float type

float float_parse_s(char * text);
float * float_parse(float * out, char * text);
char * float_tostring(const float * e, char * mem);
bool float_equals(const float * e1, const float * e2);
int float_naturalorder(const float * e1,const float * e2);

extern type int_type;

// double type

double double_parse_s(char * text);
double * double_parse(double * out, char * text);
char * double_tostring(const double * e, char * mem);
bool double_equals(const double * e1, const double * e2);
int double_naturalorder(const double * e1, const double * e2);

extern type double_type;

// int_pair

typedef struct{
	int a;
	int b;
}int_pair;

int_pair int_pair_parse_s(char * text);
int_pair * int_pair_parse(int_pair * out, char * text);
char * int_pair_tostring(const int_pair * t, char * mem);
bool int_pair_equals(const int_pair * t1, const int_pair * t2);
int int_pair_naturalorder(const int_pair * t1,const int_pair * t2);


extern type int_pair_type;

// punto

typedef struct {
	double x;
	double y;
} punto;


typedef enum {PRIMERO,SEGUNDO,TERCERO,CUARTO} Cuadrante;


double punto_distancia_al_origen(const punto * p);
int punto_ord_distancia_al_origen(const punto * p1, const punto * p2);


Cuadrante punto_cuadrante(const punto * p);

punto punto_parse_s(char * text);
punto * punto_parse(punto * out, char * text);
char * punto_tostring(const punto * p, char * mem);
bool punto_equals(const punto * p1, const punto * p2);
int punto_naturalorder(const punto * t1,const  punto * t2);

extern type punto_type;

// pair type

typedef struct {
	void * key;
	void * value;
} pair;

void * pair_to_key(void * out, pair * in);
void * pair_to_value(void * out, pair * in);

typedef struct {
	void * key;
	int n;
}pair_enumerate;

typedef struct {
	void * key;
	void * value;
	type * key_type;
	type * value_type;
} pair_t;

pair_t * pair_t_parse(pair_t * out, char * text);
char * pair_t_tostring(const pair_t * e, char * mem);
bool pair_t_equals(const pair_t * e1, const pair_t * e2);
int pair_t_naturalorder(const pair_t * e1, const pair_t * e2);


pair_t pair_t_of(pair * p, type * t1, type * t2);
pair_t pair_t_of_2(void * key, void * value, type * t1, type * t2);

extern type pair_type;

// string type

#define Tam_String 256

//typedef char string[Tam_String];

typedef struct {
	int tam;
	int size;
	char * data;
} string;

string * string_parse_out(string * out, char * text);
char * string_tostring(const string * e, char * mem);
bool string_equals(const string * e1, const string * e2);
int string_naturalorder(const string * e1,const  string * e2);


extern type string_type;

string string_empty();
bool string_is_empty(string * in);
bool string_not_is_empty(string * in);
string string_of_pchar(const char * initial);

void * string_add_pchar(string * out, const char * in_char);
void * string_add_string(string * out, const string * in);

void string_clear(string * in);

void string_free(string * in);

// pchar type

char * remove_eol_s(char * string);
char *  remove_eol(char * out, char * in);
void * pchar_concat(char * out, const char * in_string);

char * pchar_to_string(string * out, const char * in);

char * pchar_parse(char * out, char * text);
char * pchar_tostring(const char * e, char * mem);
bool pchar_equals(const char * e1, const char * e2);
int pchar_naturalorder(const char * e1,const char * e2);

bool pchar_is_empty(char * in);
bool pchar_not_is_empty(char * in);
bool pchar_all_space(char * in);
bool pchar_not_all_space(char * in);


extern type pchar_type;

// optional type

typedef struct {
	void * value;
	type * type;
} optional;

optional * optional_parse(optional * out, char * text);
char * optional_tostring(const optional * e, char * mem);
bool optional_equals(const optional * e1, const optional * e2);
int optional_naturalorder(const optional * e1, const optional * e2);


optional optional_of(void * in, type * type);
bool is_present(optional * in);

extern type optional_type;

//

extern type null_type;


// utilities

void * copy(void * out, void * in, int size);
void * copy_and_mem(void * in, int size);
void * copy_in_pointer(void ** out, void * in, int size);
void * swap(void * out, void * in, int size);

void test_string();
void test_types();

//definitions



#endif /* TYPES_H_ */
