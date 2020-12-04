/*
 * ejemplos4.c
 *
 *  Created on: 21 oct. 2020
 *      Author: migueltoro
 */

#include "../ejemplos/ejemplos4.h"

void testEjercicio1(char * path){
	char mem[10000];
	iterator it = file_iterable_pchar(path);
	list listaPrimos = list_empty(int_type);
	while(iterable_has_next(&it)){
		char * linea = (char*) iterable_next(&it);
		iterator it2 = text_to_iterable_pchar(linea, " ,");
		while(iterable_has_next(&it2)){
			char *trozos = (char*) iterable_next(&it2);
			int num  = int_parse_s(trozos);
			if(es_primo(num)){
				list_add(&listaPrimos,&num);
			}
		}
	}
	printf("Lista de Primos: %s", list_tostring(&listaPrimos, mem));
}

void test_ejemplos4() {
	testEjercicio1("ficheros/datos_entrada.txt");
}
