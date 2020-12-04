/*
 * peconditions.c
 *
 *  Created on: 10 jul. 2019
 *      Author: migueltoro
 */

#include "../types/preconditions.h"
#include <assert.h>

void check_argument(bool condition, char * file, int line, char * format,...){
	if(!condition){
		char context[256];
		sprintf(context," en fichero %s linea %d\n",file,line);
		char message[256];
		strcpy(message,format);
		strcat(message,context);
		va_list args;
		va_start(args,format);
		vfprintf(stderr,message,args);
		va_end(args);
		assert(false);
	}
}
void * check_not_null(void * reference, char * file, int line, char * message){
	if(reference == NULL){
		fprintf(stderr,"%s en fichero %s linea %d\n",message,file,line);
		assert(false);
	}
	return reference;
}

int check_element_index(int index, int size, char * file, int line){
	if(!(index>=0 && index<size)){
		fprintf(stderr,"Index = %d, size %d en fichero %s linea %d\n",index,size, file, line);
		assert(false);
	}
	return index;
}

int check_position_index(int index, int size, char * file, int line){
	if(!(index>=0 && index<=size)){
		fprintf(stderr,"Index = %d, size %d en fichero %s linea %d\n",index,size, file, line);
		assert(false);
	}
	return index;
}
