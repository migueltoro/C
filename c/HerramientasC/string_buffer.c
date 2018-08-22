/*
 * string_buffer.c
 *
 *  Created on: 9 ago. 2018
 *      Author: migueltoro
 */



#include "string_buffer.h"



string_buffer string_buffer_create(char * separator, char * prefix,char * sufix){
	string_buffer buffer = {0,separator,prefix,sufix};
	return buffer;
}

void string_buffer_add_prefix(string_buffer * buffer){
	printf("%s", buffer->prefix);
}

void string_buffer_add_sufix(string_buffer * buffer){
	printf("%s", buffer->sufix);
}

void string_buffer_add_separator(string_buffer * buffer){
	printf("%s", buffer->separator);
}

void string_buffer_close(string_buffer * buffer){
	buffer->number = 0;
}

void string_buffer_add(string_buffer * buffer, char * string) {
	if(buffer->number != 0) printf(buffer->separator);
	buffer->number = buffer->number+1;
	printf("%s", string);
}



void string_buffer_free(string_buffer * buffer){

}


