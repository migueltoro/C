/*
 * ejemplos5.c
 *
 *  Created on: 28 nov. 2020
 *      Author: migueltoro
 */


#include "ejemplos5.h"

int p(int * b, int i, int j){
	int a = *(b+2*i+j);
	return a;
}

void test_ej_5(){
	int a[2][2] = {{1,2},{3,4}};
	int * b = (int *) a;
	printf("%d",p(b,1,0));
}
