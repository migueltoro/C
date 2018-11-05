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
#include <stdbool.h>

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
bool es_par(int a);
/**
 * @param a Un entero
 * @return Si es impar
 */
bool es_impar(int a);
/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Si a es divisible por b
 */
bool es_divisible_int(int a, int b);
bool es_divisible_long(long a, long b);
/**
 * @param a Un entero
 * @return Si a es primo
 */
bool es_primo(long a);
/**
 * @param a Un entero
 * @return Siguiente primo
 */
long siguiente_primo(long a);
/**
 * @pre b &gt; a
 * @param a L�mite inferior
 * @param b L�mite Superior
 * @return Un entero aleatorio r tal que a &le; = r &lt; b
 */
int get_entero_aleatorio(int a, int b);
/**
 * @pre b &gt; a
 * @param a L�mite inferior
 * @param b L�mte Superior
 * @return Un double aleatorio que  est� en el intervalo  a &le; = r &lt; b
 */
double get_double_aleatorio(double a, double b);
/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Calcula el m�ximo com�n divisor de los valores ablsolutos de los par�metros
 */
long mcd(long a, long b);

#endif /* NEW_MATH_H_ */
