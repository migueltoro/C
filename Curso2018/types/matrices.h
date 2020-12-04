/*
 * matrices.h
 *
 *  Created on: 13 dic. 2019
 *      Author: migueltoro
 */

#ifndef MATRICES_H_
#define MATRICES_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "preconditions.h"
#include "types.h"
#include "list.h"

typedef struct {
	int * datos;
	int __n;
	int iv;
	int nf;
	int jv;
	int nc;
}matrix;

typedef struct {
	matrix m0;
	matrix m1;
	matrix m2;
	matrix m3;
}matrix_views;

matrix matrix_of_array(int * a, int nf, int nc);
matrix matrix_of_file(char * file, void * array, type type);

int matrix_get(matrix s, int i, int j);
int matrix_nf(matrix s);
int matrix_nc(matrix s);
void matrix_set(matrix s, int i, int j, int value);

matrix matrix_view(matrix s, int ns);
void matrix_print(matrix s, char * text);
void matrix_copy(matrix in, matrix out);
matrix_views views_of_matrix(matrix s);

void multiply_iterativa(matrix out, matrix in1, matrix in2);
void multiply_recursiva(matrix out, matrix in1, matrix in2);
void sum_iterativa(matrix out, matrix in1, matrix in2);
void sum_recursiva(matrix out, matrix in1, matrix in2);

void test_matrices();
void test_matrices_2();
void test_matrices_3();

#endif /* MATRICES_H_ */
