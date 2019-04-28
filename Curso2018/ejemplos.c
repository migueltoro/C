/*
 * ejemplos.c
 *
 *  Created on: 19 nov. 2018
 *      Author: migueltoro
 */

#include "ejemplos.h"

memory_heap hp;

double n_problema1(alist ls){
	double sum = 0.;
	for(int i=0;i<ls.size;i++){
		sum = sum + *(double*) alist_get(&ls,i);
	}
	return sum;
}

alist n_problema2(alist ls) {
	alist r = alist_empty(ls.size);
	for (int i = 0; i < ls.size; i++) {
		double x = (*(punto*)alist_get(&ls,i)).x;
		alist_add(&r,to_data(&x,sizeof(double),&hp));
	}
	return r;
}

bool n_problema3(alist ls, bool (*p)(int e)) {
	bool b = true;
	int i = 0;
	while (i < ls.size && b) {
		b = p(*(int*)alist_get(&ls,i));
		i++;
	}
	return b;
}

bool n_problema4(alist ls, bool (*p)(int e)) {
	bool b = false;
	int i = 0;
	while (i < ls.size && !b) {
		b = p(*(int*)alist_get(&ls,i));
		i++;
	}
	return b;
}

int n_problema5(alist ls) {
	int sum = 0;
	for (int i = 0; i < ls.size; i++) {
		int e = *(int*)alist_get(&ls,i);
		int t = e * e;
		sum = sum + t;
	}
	return sum;
}

double n_problema6(alist ls, double umbral) {
	double b;
	int p = 0;
	int i = 0;
	while (i < ls.size && p == 0) {
		double e = *(double*) alist_get(&ls,i);
		if (e > umbral) {
			p++;
			b = e;
		}
		i++;
	}
	return b;
}

punto * n_problema8(alist ls, int (*cmp)(const void *, const void *)) {
	punto * r = NULL;
	for (int i = 0; i < ls.size; i++) {
		punto * p = (punto *) alist_get(&ls,i);
		if (r == NULL || cmp(p, r) > 0)
			r = p;
	}
	return r;
}

hash_table n_problema11(alist ls){
	hash_table r = hash_table_empty(int_equals,int_tostring);
	for (int i = 0; i < ls.size; i++) {
		punto * p = (punto *) alist_get(&ls,i);
		Cuadrante c = punto_cuadrante(*p);
		void * pc = to_data(&c,sizeof(Cuadrante),&hp);
		alist * ls;
		if(hash_table_contains(&r,&c)){
			ls = hash_table_get(&r,pc);
			alist_add(ls,p);
		} else {
			alist ls1 = alist_empty();
			alist_add(&ls1,p);
			void * pls = to_data(&ls1,sizeof(alist),&hp);
			hash_table_put(&r,pc,pls);
		}
	}
	return r;
}

alist n_problema61(char * file){
	alist r = alist_empty();
	file_iterator f = open_file(file);
	while(has_next_line(&f)){
		char * s = next_line(&f);
		punto e = punto_parse(s);
		void * pe = to_data(&e,sizeof(punto),&hp);
		alist_add(&r,pe);
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

void test_ejemplos(){
	hp = memory_heap_create();

	printf("\n\n");

	double d1[] = { 45., 56, 90., 1., 23., 78., 76. };
	alist ls1 = alist_of(d1, 7, sizeof(double));
	double r1 = n_problema1(ls1);
	printf("r1 = %lf\n", r1);

	printf("\n\n");

	char mem[256];
	punto ap[] = { { 1., 2. }, { -1., 2.1 }, { 3.1, 2.1 }, { 1.3, 27.0 }, { 1.,-2. } };
	alist r2 = alist_of(ap, 5, sizeof(punto));
	alist rp = n_problema2(r2);
	char * s = alist_tostring(&r2, punto_tostring,mem);
	printf("%s\n",s);
	s = alist_tostring(&rp, double_tostring,mem);
	printf("%s\n",s);

	printf("\n\n");

	int d3[] = {45, 57, 10, 1, 23, 77, 79};
	alist ls3 = alist_of(d3, 7, sizeof(int));
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

	alist puntos = n_problema61("prueba.txt");
	s = alist_tostring(&puntos,punto_tostring,mem);
	printf("%s\n",s);

	n_problema59("primos.txt", 200);

	printf("\n\n");

	hash_table t2 = n_problema11(r2);
	alist * r;
	for(int i=0;i<4;i++){
		r = hash_table_get(&t2,&i);
		if (r!=NULL) {
			s = alist_tostring(r,punto_tostring,mem);
			printf("%d == %s\n",i, s);
		}
	}

	memory_heap_free(&hp);
}
