/*
 * ejemplos.c
 *
 *  Created on: 19 nov. 2018
 *      Author: migueltoro
 */

#include "ejemplos.h"

memory_heap hp;

double n_problema1(list ls){
	double sum = 0.;
	for(int i=0;i<ls.size;i++){
		sum = sum + *(double*) list_get(&ls,i);
	}
	return sum;
}

list n_problema2(list ls) {
	list r = list_empty(double_type);
	for (int i = 0; i < ls.size; i++) {
		double x = (*(punto*)list_get(&ls,i)).x;
		list_add(&r,&x);
	}
	return r;
}

bool n_problema3(list ls, bool (*p)(int e)) {
	bool b = true;
	int i = 0;
	while (i < ls.size && b) {
		b = p(*(int*) list_get(&ls,i));
		i++;
	}
	return b;
}

bool n_problema4(list ls, bool (*p)(int e)) {
	bool b = false;
	int i = 0;
	while (i < ls.size && !b) {
		b = p(*(int*) list_get(&ls,i));
		i++;
	}
	return b;
}

int n_problema5(list ls) {
	int sum = 0;
	for (int i = 0; i < ls.size; i++) {
		int e = *(int*) list_get(&ls,i);
		int t = e * e;
		sum = sum + t;
	}
	return sum;
}

double n_problema6(list ls, double umbral) {
	double b;
	int p = 0;
	int i = 0;
	while (i < ls.size && p == 0) {
		double e = *(double *) list_get(&ls,i);
		if (e > umbral) {
			p++;
			b = e;
		}
		i++;
	}
	return b;
}

punto * n_problema8(list ls, int (*cmp)(const void *, const void *)) {
	punto * r = NULL;
	for (int i = 0; i < ls.size; i++) {
		punto * p = (punto *) list_get(&ls,i);
		if (r == NULL || cmp(p, r) > 0)
			r = p;
	}
	return r;
}

hash_table n_problema11(list ls){
	hash_table r = hash_table_empty(int_type,list_type);
	for (int i = 0; i < ls.size; i++) {
		punto * p = (punto *) list_get(&ls,i);
		Cuadrante c = punto_cuadrante(p);
		if(hash_table_contains(&r,&c)){
			list * ls = hash_table_get(&r,&c);
			list_add(ls,p);
		} else {
			list ls = list_empty(punto_type);
			list_add(&ls,p);
			hash_table_put(&r,&c,&ls);
		}
	}
	return r;
}

list n_problema61(char * file){
	list r = list_empty(punto_type);
	iterator f = file_iterable_pchar(file);
	while(iterable_has_next(&f)){
		char * s = (char *) iterable_next(&f);
		punto e = punto_parse_s(s);
		list_add(&r,&e);
	}
	return r;
}

void n_problema59(char * file, long n) {
	long i = 2;
	FILE * st = fopen(file, "wt");
	assert(st != NULL && "no se encuentra el fichero");
	while (i < n) {
		fprintf(st, "%ld\n", i);
		i = siguiente_primo(i);
	}
	fclose(st);
}

int nn = 200;

bool has_next_primo(long * in){
	return *in < nn;
}

void * next_primo(long * out, long *in){
	*out = siguiente_primo(*in);
	return out;
}

void n_problema59_b(char * file, long n){
	long ini = 2;
	iterator st = iterable_iterate(sizeof(long),&ini,has_next_primo,next_primo);
	write_iterable_to_file(file,&st,long_tostring);
}

void test_ejemplos(){
//	hp = memory_heap_create();

	printf("\n\n");

	double d1[] = { 45., 56, 90., 1., 23., 78., 76. };
	list ls1 = list_of(d1, 7, double_type);
	double r1 = n_problema1(ls1);
	printf("r1 = %lf\n", r1);

	printf("\n\n");

	char mem[256];
	char * s;
	punto ap[] = { { 1., 2. }, { -1., 2.1 }, { 3.1, 2.1 }, { 1.3, 27.0 }, { 1.,-2. } };
	list r2 = list_of(ap, 5, punto_type);
	list rp = n_problema2(r2);
	s = list_tostring(&r2,mem);
	printf("%s\n",s);
	s = list_tostring(&rp,mem);
	printf("%s\n",s);

	printf("\n\n");

	int d3[] = {45, 57, 10, 1, 23, 77, 79};
	list ls3 = list_of(d3, 7,int_type);
	bool r3 = n_problema3(ls3, es_impar);
	printf("r3 = %s\n", r3 ? "true" : "false");

	printf("\n\n");

	bool r4 = n_problema4(ls3, es_impar);
	printf("r4 = %s\n", r4 ? "true" : "false");

	printf("\n\n");

	int r5 = n_problema5(ls3);
	printf("r5 = %d\n", r5);

	printf("\n\n");

	double r6 = n_problema6(ls1, 60.);
	printf("r6 = %lf\n", r6);

	printf("\n\n");

	punto * p = n_problema8(r2, punto_naturalorder);
	printf("%s\n",punto_tostring(p,mem));

	printf("\n\n");

	list puntos = n_problema61("prueba.txt");
	s = list_tostring(&puntos,mem);
	printf("%s\n",s);

	n_problema59("primos.txt", 200);
	n_problema59_b("primos_2.txt", 200);

	printf("\n\n");

	hash_table t2 = n_problema11(r2);
	list * r;
	for(int i=0;i<4;i++){
		r = hash_table_get(&t2,&i);
		if (r!=NULL) {
			s = list_tostring(r,mem);
			printf("%d == %s\n",i, s);
		}
	}

//	memory_heap_free(&hp);
}
