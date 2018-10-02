/*
 * ejemplos.h
 *
 *  Created on: 26 sept. 2018
 *      Author: migueltoro
 */

#ifndef EJEMPLOS_H_
#define EJEMPLOS_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "basic_types.h"

typedef struct {
	int tam;
	int size;
	double * data;
}double_list;

typedef struct {
	int tam;
	int size;
	int * data;
}int_list;

typedef struct {
	int tam;
	int size;
	punto * data;
}punto_list;

#define Tma_String 256

typedef struct{
	FILE * file;
	bool is_done;
	bool has_next;
	char next[256];
}file_iterator;


double_list create_double_list(double * data, int tam, int size);

double_list empty_double_list(int tam);

void imprime_list_double(double_list, char * s, char * p, char * f); // problema 50

int_list create_int_list(int * data, int tam, int size);

int_list empty_int_list(int tam);

void imprime_list_int(int_list, char * s, char * p, char * f); // problema 50

punto_list create_punto_list(punto * data, int tam, int size);

punto_list empty_punto_list(int tam);

void imprime_list_punto(punto_list, char * s, char * p, char * f); // problema 50

double problema1(double_list ls);

double_list problema2(punto_list ls);

bool problema3(int_list ls, bool (*p)(int e));

bool problema4(int_list ls, bool (*p)(int e));

double problema5(int_list ls);

double problema6(double_list ls, double umbral);

punto * problema8(punto_list ls, int (*cmp)(punto *,punto *));

bool es_primo(int n);  //problema 18

file_iterator open_file(char * file);

bool has_next_line(file_iterator * it);

char * next_line(file_iterator * it);

punto_list list_punto_from_file(char * file); //similar al problema 61 pero leyendo un punto por linea en vez de un entero

#endif /* EJEMPLOS_H_ */