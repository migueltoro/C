/*
 * new_math.h
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */

#ifndef NEW_MATH_H_
#define NEW_MATH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

/**
 * @param a Un entero
 * @return Si es par
 */
int esPar(int a);
/**
 * @param a Un entero
 * @return Si es impar
 */
int esImpar(int a);
/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Si a es divisible por b
 */
int esDivisible_int(int a, int b);
int esDivisible_long(long a, long b);
/**
 * @param a Un entero
 * @return Si a es primo
 */
int esPrimo(long a);
/**
 * @param a Un entero
 * @return Siguiente primo
 */
long siguientePrimo(long a);
/**
 * @pre b &gt; a
 * @param a Límite inferior
 * @param b Límite Superior
 * @return Un entero aleatorio r tal que a &le; = r &lt; b
 */
int getEnteroAleatorio(int a, int b);
/**
 * @pre b &gt; a
 * @param a Límite inferior
 * @param b Límte Superior
 * @return Un double aleatorio que  está en el intervalo  a &le; = r &lt; b
 */
double getDoubleAleatorio(double a, double b);
/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Calcula el máximo común divisor de los valores ablsolutos de los parámetros
 */
int mcd(int a, int b);

void * sum_long_int(void * base, void * value);

#endif /* NEW_MATH_H_ */
