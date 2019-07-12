/*
 * peconditions.c
 *
 *  Created on: 10 jul. 2019
 *      Author: migueltoro
 */

#include "../types/preconditions.h"
#include <assert.h>



void check_argument(bool condition, char * file, int line, char * message){
	if(!condition){
		fprintf(stderr,"%s en %s linea %d \n",message,file,line);
		assert(false);
	}
}
void * check_not_null(void * reference, char * file, int line, char * message){
	if(reference == NULL){
		fprintf(stderr,"%s en %s linea %d\n",message,file,line);
		assert(false);
	}
	return reference;
}

int check_element_index(int index, int size, char * file, int line){
	if(!(index>=0 && index<size)){
		fprintf(stderr,"Index = %d, size %d en %s linea %d\n",index,size, file, line);
		assert(false);
	}
	return index;
}

int check_position_index(int index, int size, char * file, int line){
	if(!(index>=0 && index<=size)){
		fprintf(stderr,"Index = %d, size %d en %s linea %d\n",index,size, file, line);
		assert(false);
	}
	return index;
}
