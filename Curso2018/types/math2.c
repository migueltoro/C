/*
 * new_math.c
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */


#include "../types/math2.h"
;
/**
 * @param a Un entero
 * @return Si es par
 */
bool es_par(int a) {
	return a % 2 == 0;
}

/**
 * @param a Un entero
 * @return Si es impar
 */
bool es_impar(int a) {
	return !es_par(a);
}

/**
 * @param a Un entero
 * @param b Un segundo entero
 * @return Si a es divisible por b
 */

bool es_divisible_int(int a, int b) {
	return (a % b) == 0;
}

bool es_divisible_long(long a, long b) {
	return (a % b) == 0;
}
/**
 * @param a Un entero
 * @return Si a es primo
 */


bool es_primo(long n) {  //problema 18
	long sq = (long) sqrt((double) n);
	int e = 2;
	bool a = false;
	while (e <= sq && !a) {
		a = (n%e==0);
		e = e + 1;
	}
	return !a;
}

/**
 * @param a Un entero
 * @return Siguiente primo
 */

long siguiente_primo(long a) {
	long x;
	for (x = a + 1; 1; x = x + 1) {
		if (es_primo(x))
			break;
	}
	return x;
}

void new_rand(){
	time_t t;
	srand((unsigned) time(&t));
}


/**
 * @pre b &gt; a
 * @param a Límite inferior
 * @param b Límite Superior
 * @return Un entero aleatorio r tal que a &le; = r &lt; b
 */


int get_entero_aleatorio(int a, int b) {
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
double get_double_aleatorio(double a, double b) {
	double r = ((double) rand() / (RAND_MAX));
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
