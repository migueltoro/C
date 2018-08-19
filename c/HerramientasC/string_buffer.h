/*
 * string_buffer.h
 *
 *  Created on: 9 ago. 2018
 *      Author: migueltoro
 */

#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

#include "basic_types.h"

typedef struct {
	int is_first;
	int number;
	char * separator;
	char * prefix;
	char * sufix;
} string_buffer;

string_buffer string_buffer_create(char * separator, char * prefix,char * sufix);
void string_buffer_add(string_buffer * buffer, char * string);
void string_buffer_clear(string_buffer * buffer);
void string_buffer_free(string_buffer * buffer);

#endif /* STRING_BUFFER_H_ */
