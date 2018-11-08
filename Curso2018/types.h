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
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "new_math.h"

unsigned long int hash(const char * key);


// int type

char * int_tostring(const void * e, char * mem);
int int_equals(const void * e1, const void * e2);
int int_naturalorder(const void * e1, const void * e2);

// long type

char * long_tostring(const void * e, char * mem);
int long_equals(const void * e1, const void * e2);
int long_naturalorder(const void * e1, const void * e2);

// float type

char * float_tostring(const void * e, char * mem);
int float_equals(const void * e1, const void * e2);
int float_naturalorder(const void * e1,const  void * e2);

// double type

char * double_tostring(const void * e, char * mem);
int double_equals(const void * e1, const void * e2);
int double_naturalorder(const void * e1,const  void * e2);

// string type

#define Tam_String 256

typedef char string[Tam_String];

char * string_tostring(const void * e, char * mem);
int string_equals(const void * e1, const void * e2);
int string_naturalorder(const void * e1,const  void * e2);

char * remove_eol(char * string);

typedef struct{
	int a;
	int b;
}int_pair;

char * int_pair_tostring(const void * t, char * mem);
int int_pair_equals(const void * t1, const void * t2);
int int__naturalorder(const void * t1,const  void * t2);

// punto

typedef struct {
	double x;
	double y;
} punto;


typedef enum {PRIMERO,SEGUNDO,TERCERO,CUARTO} Cuadrante;


double punto_distancia_al_origen(const punto p);
int punto_ord_distancia_al_origen(const punto p1, const punto p2);

Cuadrante punto_cuadrante(const punto p);

char * punto_tostring(const void * p, char * mem);
int punto_equals(const void * p1, const void * p2);
int punto_naturalorder(const void * t1,const  void * t2);


// time.h


char * time_tostring(const void * p, char * mem);
int time_equals(const void * p1, const void * p2);
int time_naturalorder(const void * t1,const  void * t2);

#endif /* TYPES_H_ */
