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

punto_list list_punto_from_file(char * file); //similar al problema 61 pero leyendo un punto por linea en vez de un entero

void problema59(char * file,long n);

#endif /* FILES_H_ */
