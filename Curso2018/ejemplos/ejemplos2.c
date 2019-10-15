/*
 * ejemplos2.c
 *
 *  Created on: 14 oct. 2019
 *      Author: migueltoro
 */


#include "ejemplos2.h"

long sum_primos_file(char * file){
	iterator it = file_iterable_pchar(file);
	long sum = 0;
	while(iterable_has_next(&it)){
		char * line = (char *) iterable_next(&it);
		long e;
		long_type.parse(&e,line);
		if(es_primo(e)){
			sum = sum +e;
		}
	}
	return sum;
}

int count_primos_file(char * file){
	iterator it = file_iterable_pchar(file);
	long sum = 0;
	while(iterable_has_next(&it)){
		char * line = (char *) iterable_next(&it);
		long e;
		long_type.parse(&e,line);
		if(es_primo(e)){
			sum = sum +1;
		}
	}
	return sum;
}

int count_primos_file_2(char * file){
	iterator it = file_iterable_pchar(file);
	long sum = 0;
	while(iterable_has_next(&it)){
		char * line = (char *) iterable_next(&it);
		iterator it2 = split_iterable_pchar(line," ,");
		while(iterable_has_next(&it2)) {
			char * num = (char *) iterable_next(&it2);
			long e;
			long_type.parse(&e,num);
			if(es_primo(e)){
				sum = sum +1;
			}
		}
	}
	return sum;
}

bool is_palindrome(list * ls){
	int i = 0;
	int n = list_size(ls);
	bool r = true;
	while(n-2*i-1>0 && r){
		r = *(int *)list_get(ls,i) == *(int *)list_get(ls,n-i-1);
		i = i+1;
	}
	return r;
}

void test_ejemplos2(){
	int r = sum_primos_file("ficheros/numeros.txt");
	printf("r = %d\n",r);
	int np = count_primos_file("ficheros/numeros.txt");
	printf("np = %d\n",np);
	np = count_primos_file_2("ficheros/numeros2.txt");
	printf("np2 = %d\n",np);
	int dt[] = {1,2,0,4,5,4,3,2,1};
	list ls = list_of(dt,9,int_type);
	bool s = is_palindrome(&ls);
	printf("s = %s\n",s?"true":"false");
}
