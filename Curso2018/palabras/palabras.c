/*
 * palabras.c
 *
 *  Created on: 22 jul. 2019
 *      Author: migueltoro
 */

#include "palabras.h"

int numero_de_palabras(char * file) {
	iterator git1 = file_iterable_pchar(file);
	iterator git2 = iterable_filter(&git1, pchar_not_all_space);
	iterator git3 = iterable_map(&git2,pchar_type, pchar_remove_eol);
	iterator gmap = iterable_flatmap(&git3,pchar_type,text_to_iterable_pchar_function);
	int n = iterable_size(&gmap);
	iterable_free(&git1);
	iterable_free(&git2);
	iterable_free(&git3);
	iterable_free(&gmap);
	return n;
}

int numero_de_palabras_distintas(char * file) {
	iterator git1 = file_iterable_pchar(file);
	iterator git2 = iterable_filter(&git1, pchar_not_all_space);
	iterator git3 = iterable_map(&git2,pchar_type, pchar_remove_eol);
	iterator gmap = iterable_flatmap(&git3,pchar_type,text_to_iterable_pchar_function);
	int n = iterable_size(&gmap);
	iterable_free(&git1);
	iterable_free(&git2);
	iterable_free(&git3);
	iterable_free(&gmap);
	return n;
}

char * identity(char * out, char * in){
	strcpy(out,in);
	return in;
}

hash_table frecuencias_de_palabras(char * file) {
	iterator git1 = file_iterable_pchar(file);
	iterator git2 = iterable_filter(&git1, pchar_not_all_space);
	iterator git3 = iterable_map(&git2,pchar_type, pchar_remove_eol);
	iterator gmap = iterable_flatmap(&git3,pchar_type,text_to_iterable_pchar_function);
	type pc = pchar_type;
	pc.size = 20;
	hash_table r = iterable_counting(&gmap,identity,pc);
	return r;
}

char * pair_pchar_int(pair * in, char * mem){
	sprintf(mem,"(%s,%d)", (char *) in->key,*(int*) in->value );
	return mem;
}

void test_palabras() {
	int n = numero_de_palabras("ficheros/quijote.txt");
	printf("%d\n", n);
	hash_table fq = frecuencias_de_palabras("ficheros/quijote.txt");
	iterator ifq = hash_table_items_iterable(&fq);
	iterable_toconsole_sep(&ifq,pair_pchar_int,"\n","\n","\n");
}


