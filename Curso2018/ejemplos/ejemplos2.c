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
	int sum = 0;
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
	int sum = 0;
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

list file_to_list(char * file){
       iterator it = file_iterable_pchar(file);
       list ls = list_empty(long_type);
       while(iterable_has_next(&it)){
             char * line = (char *) iterable_next(&it);
             iterator it2 = split_iterable_pchar(line," ,");
             while(iterable_has_next(&it2)) {
                    char * num = (char *) iterable_next(&it2);
                    long e;
                    long_type.parse(&e,num);
                    if (e%2 == 0) {
                        e = e*e;
                        list_add(&ls, &e);
                    }
             }
       }
       return ls;
}

list file_to_list_2(char * file) {
	iterator f = file_iterable_pchar(file);
	list ls = list_empty(long_type);
	while (iterable_has_next(&f)) {
		char * linea = iterable_next(&f);
		char * tt[20];
		int n = split_text(linea, " ,", tt);
		for (int i = 0; i < n; i++) {
			int e = long_parse_s(tt[i]);
			if (e%2 == 0) {
				e = e * e;
				list_add(&ls, &e);
			}
		}
	}
	return ls;
}

list file_to_list_of_list(char * file){
	list res = list_empty(list_type);
	iterator it1 = file_iterable_pchar(file);
	while(iterable_has_next(&it1)) {
	      char* linea = (char*)iterable_next(&it1);
	      list ls = list_empty(int_type);
	      iterator it2 = split_iterable_pchar(linea, " ,");
	      while(iterable_has_next(&it2)) {
	    	  	char * tx = iterable_next(&it2);
	            int x;
	            int_type.parse(&x,tx);
                list_add(&ls, &x);
	      }
	      list_add(&res, &ls);
	}
	return res;
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
	char mem[1500];
//	int r = sum_primos_file("ficheros/numeros.txt");
//	printf("r = %d\n",r);
//	int np = count_primos_file("ficheros/numeros.txt");
//	printf("np = %d\n",np);
//	np = count_primos_file_2("ficheros/numeros2.txt");
//	printf("np2 = %d\n",np);
//	int dt[] = {1,2,0,4,5,4,3,2,1};
//	list ls = list_of(dt,9,int_type);
//	bool s = is_palindrome(&ls);
//	printf("s = %s\n",s?"true":"false");
//	list ls2 = file_to_list("ficheros/numeros2.txt");
//	char * s2 = list_tostring(&ls2,mem);
//	printf("\n%s\n", s2);
//	ls2 = file_to_list_2("ficheros/numeros2.txt");
//	s2 = list_tostring(&ls2,mem);
	list ls3 = file_to_list_of_list("ficheros/datos_entrada.txt");
	char * s2 = list_tostring(&ls3,mem);
	printf("\n%s\n", s2);
}
