/*
 * new_math.c
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */


#include "new_math.h"

/**
 * @param a Un entero
 * @return Si es par
 */
bool esPar(int a) {
	return a % 2 == 0;
}

/**
 * @param a Un entero
 * @return Si es impar
 */
bool esImpar(int a) {
	return !esPar(a);
}

/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Si a es divisible por b
 */

bool esDivisible_int(int a, int b) {
	return (a % b) == 0;
}

bool esDivisible_long(long a, long b) {
	return (a % b) == 0;
}
/**
 * @param a Un entero
 * @return Si a es primo
 */

bool esPrimo(long a) {
	long sq = (long) sqrt((double) a);
	long i;
	int r = 0;
	for (i = 2; i <= sq; i++) {
		r = esDivisible_long(a, i);
		if (r)
			break;
	}
	return !r;
}

/**
 * @param a Un entero
 * @return Siguiente primo
 */

long siguientePrimo(long a) {
	long x;
	for (x = a + 1; 1; x = x + 1) {
		if (esPrimo(x))
			break;
	}
	return x;
}

/**
 * @pre b &gt; a
 * @param a Límite inferior
 * @param b Límite Superior
 * @return Un entero aleatorio r tal que a &le; = r &lt; b
 */

int getEnteroAleatorio(int a, int b) {
	long valor;
	if (b - a == 1) {
		valor = a;
	} else {
		valor = a + rand() % (b - a);
	}
	return valor;
}

/**
 * @pre b &gt; a
 * @param a Límite inferior
 * @param b Límte Superior
 * @return Un double aleatorio que  está en el intervalo  a &le; = r &lt; b
 */
double getDoubleAleatorio(double a, double b) {
	double r = ((double) getEnteroAleatorio(0, 1000)) / 1000.;
	r = a + (b - a) * r;
	return r;
}

/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Calcula el máximo común divisor de los valores ablsolutos de los parámetros
 */
long mcd(long a, long b) {
	int u = abs(a);
	int v = abs(b);
	int r;
	while (v != 0) {
		r = u % v;
		u = v;
		v = r;
	}
	return u;
}

void * sum_long_int(void * base, void * value) {
	long * b = (long*) base;
	int v = *(int*) value;
	*b = *b + v;
	return base;
}
