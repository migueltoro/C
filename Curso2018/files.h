/*
 * files.h
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#ifndef FILES_H_
#define FILES_H_


#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "types.h"
#include "primeros_ejemplos.h"

typedef struct{
	FILE * file;
	bool is_done;
	bool has_next;
	char next[256];
}file_iterator;

file_iterator open_file(char * file);

bool has_next_line(file_iterator * it);

char * next_line(file_iterator * it);


#endif /* FILES_H_ */
