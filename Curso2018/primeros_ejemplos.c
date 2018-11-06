/*
 * ejemplos.c
 *
 *  Created on: 26 sept. 2018
 *      Author: migueltoro
 */

#include "primeros_ejemplos.h"
#include "types.h"

double_list create_double_list(double * data, int tam, int size) {
	double_list r = {tam,size,data};
	return r;
}

double_list empty_double_list(int tam) {
	double * d = (double *) malloc(tam*sizeof(double));
	double_list r = {tam,0,d};
	return r;
}

int_list create_int_list(int * data, int tam, int size){
	int_list r = {tam,size,data};
	return r;
}

int_list empty_int_list(int tam){
	int * d = (int *) malloc(tam*sizeof(int));
	int_list r = {tam,0,d};
	return r;
}

string_list create_string_list(string * data, int tam, int size) {
	string_list r = {tam,size,data};
	return r;
}


punto_list create_punto_list(punto * data, int tam, int size){
	punto_list r = {tam,size,data};
	return r;
}

punto_list empty_punto_list(int tam){
	punto * d = (punto *) malloc(tam*sizeof(punto));
	punto_list r = {tam,0,d};
	return r;
}

double problema1(double_list ls){
	double sum = 0.;
	for(int i=0;i<ls.size;i++){
		sum = sum + ls.data[i];
	}
	return sum;
}

double_list problema2(punto_list ls){
	double_list r = empty_double_list(ls.size);
	for(int i=0;i<ls.size;i++){
		 double x = ls.data[i].x;
		 r.data[r.size] = x;
		 r.size = r.size+1;
	}
	return r;
}

bool problema3(int_list ls, bool (*p)(int e)){
	bool b = true;
	int i =0;
	while(i<ls.size && b) {
		b = p(ls.data[i]);
		i++;
	}
	return b;
}

bool problema4(int_list ls, bool (*p)(int e)){
	bool b = false;
	int i =0;
	while(i<ls.size && !b) {
		b = p(ls.data[i]);
		i++;
	}
	return b;
}

double problema5(int_list ls){
	double sum = 0.;
	for(int i=0;i<ls.size;i++){
		double e = ls.data[i];
		double t = e*e;
		sum = sum + t;
	}
	return sum;
}

double problema6(double_list ls, double umbral){
	double b;
	int p = 0;
	int i = 0;
	while(i<ls.size && p==0) {
		double e = ls.data[i];
		if(e>umbral){
			p++;
			b = e;
		}
		i++;
	}
	return b;
}

void imprime_list_punto(punto_list ls, char * s, char * p, char * f) {  //problema 50
	int n = 0;
	printf("%s", p);
	for (int i = 0; i < ls.size; i++) {
		punto e = ls.data[i];
		if (n == 0){
			printf("(%.2lf,%.2lf)", e.x, e.y);
			n++;
		} else
			printf("%s(%.2lf,%.2lf)", s, e.x, e.y);
	}
	printf("%s", f);
}

void imprime_list_double(double_list ls, char * s, char * p, char * f) { //problema 50
	int n = 0;
	printf("%s", p);
	for (int i = 0; i < ls.size; i++) {
		double e = ls.data[i];
		if (n == 0){
			printf("%.2lf", e);
			n++;
		} else
			printf("%s%.2lf", s, e);
	}
	printf("%s", f);
}

void imprime_list_string(string_list ls) {
	int n = 0;
	printf("{");
	for (int i = 0; i < ls.size; i++) {
		if (n == 0) {
			printf("%s", ls.data[i]);
			n++;
		} else
			printf("%s%s", ",", ls.data[i]);
	}
	printf("}");
}

punto * problema8(punto_list ls, int (*compare)(const void *, const void *)) {
	punto * r = NULL;
	for (int i = 0; i < ls.size; i++) {
		punto * p = ls.data+i;
		if(r == NULL || compare(p,r)>0) r = p;
	}
	return r;
}


punto_list_list empty_punto_list_list(int tam){
	punto_list * d = (punto_list *) malloc(tam*sizeof(punto_list));
	punto_list_list r = {tam,0,d};
	return r;
}

Cuadrante punto_cuadrante(const punto p);

punto_list_list problema11(punto_list ls){
	punto_list_list r = empty_punto_list_list(4);
	punto p;
	int c;
	for(int i =0; i<4; i++) {
		r.data[i] = empty_punto_list(50);
		r.size = 4;
	}
	for(int i = 0; i <ls.size; i++){
		p = ls.data[i];
		c = punto_cuadrante(p);
		int size = r.data[c].size;
		r.data[c].data[size] = p;
		r.data[c].size = r.data[c].size +1;
	}
	return r;
}

void imprime_list_list_punto(punto_list_list ls, char * s, char * p, char * f) {
	int n = 0;
	printf("%s", p);
	for (int i = 0; i < ls.size; i++) {
		if (n == 0) {
			printf("Cuadrante %d =",i);
			imprime_list_punto(ls.data[0], ",", "{", "}");
			n++;
		} else {
			printf("\n%s",s);
			printf("Cuadrante %d =",i);
			imprime_list_punto(ls.data[i],  ",", "{", "}");
		}
	}
	printf("%s", f);
}


