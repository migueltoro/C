/*
 * string_buffer.c
 *
 *  Created on: 9 ago. 2018
 *      Author: migueltoro
 */



#include "string_buffer.h"



string_buffer string_buffer_create(char * separator, char * prefix,char * sufix){
	string_buffer buffer = {1,0,separator,prefix,sufix};
	return buffer;
}

void string_buffer_add(string_buffer * buffer, char * string) {
	if(buffer->is_first){
		printf(buffer->prefix);
		buffer->is_first = 0;
	} else {
		printf(buffer->separator);
	}
	buffer->number = buffer->number+1;
	printf("%s", string);
}

void string_buffer_clear(string_buffer * buffer){
	printf(buffer->sufix);
	buffer->is_first = 1;
	buffer->number = 0;
}

void string_buffer_free(string_buffer * buffer){

}


