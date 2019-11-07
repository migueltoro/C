/*
 * ejemplos3.c
 *
 *  Created on: 23 oct. 2019
 *      Author: migueltoro
 */


#include "ejemplos3.h"

list array_tolist(char * n, int ne){
	list nls = list_empty(pchar_type);
	for(int i =0; i<ne;i++){
		list_add(&nls,n);
	}
	return nls;
}

void test_ejemplos3(){
	char nombres[][Tam_String] = {"Antonio","Pepe","Juan","Asuncion"};
	list nls = list_of(nombres,4,pchar_type);
	list_add(&nls,"Jose");
	char mem[200];
	char * s = list_tostring(&nls,mem);
	printf("%s\n",s);
	printf("%s\n",(char *)list_get(&nls,2));
}
