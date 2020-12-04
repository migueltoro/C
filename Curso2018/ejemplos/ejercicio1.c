/*
 * ejercicio1.c
 *
 *  Created on: 18 nov. 2020
 *      Author: migueltoro
 */


#include "ejercicio1.h"

//ITERATIVO
int ejercicio1iter(char* s1, char * s2){
	int n =  strlen(s1);
	int i = 0;
	int j = n;
	int k= n/2;
	int b = -1;
	while((j - i) > 0 && b == -1){
		if(s1[k] != s2[k] && s1[k-1] == s2[k-1]){
			b = k;
		}else if(s1[k] == s2[k] && s1[k-1] == s2[k-1]){
			i = k;
			k = (i+j) /2;
		}else{
			j = k;
			k = (i+j) /2;
		}
	}

	return b;
}


list leeFichero1(char* file) {
	list r = list_empty(pchar_type);
	iterator f = file_iterable_pchar(file);
	while (iterable_has_next(&f)) {
		char* s = iterable_next(&f);
		list_add(&r, s);
	}
	return r;
}

void lecturaFichero1Iter(char * fichero) {
	char mem[256];
	list l = leeFichero1(fichero);
	int i = 0;
	while (i < l.size) {
		iterator it2 = text_to_iterable_pchar(list_get(&l, i), "#");
		char* a = (char*) iterable_next(&it2);
		char* b = (char*) iterable_next(&it2);
		printf("Entrada: (%s,%s) \n", a, b);
		int sol = ejercicio1iter(a, b);
		char *s = int_tostring(&sol, mem);
		printf("Salida: %s\n", s);
		printf("========================\n");
		i++;
	}
}

void test_ejerc1(){

	printf("--------TEST DEL METODO ITERATIVO-----------\n");

	lecturaFichero1Iter("ficheros/PI2Ej1DatosEntrada.txt");

}
