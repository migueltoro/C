/*
 * more_string.h
 *
 *  Created on: 16 nov. 2018
 *      Author: migueltoro
 */

#ifndef NEW_STRING_H_
#define NEW_STRING_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "types.h"

// string type

#define Tam_String 256

typedef char string[Tam_String];

char * string_tostring(const void * e, char * mem);
int string_equals(const void * e1, const void * e2);
int string_naturalorder(const void * e1,const  void * e2);

char * remove_eol(char * string);

char ** split(char * text, const char * delimiters, char ** tokens, int * ntokens);

#endif /* NEW_STRING_H_ */
