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

#include "list.h"
#include "types.h"

typedef struct{
	FILE * file;
	bool is_done;
	bool has_next;
	char next[Tam_String];
}file_iterator;

file_iterator open_file(char * file);
bool has_next_line(file_iterator * it);
char * next_line(file_iterator * it);
void write_list_to_file(char * file, list * list, char * to_string(const void * source, char * mem));
list lines(char * file);
void test_files();


#endif /* FILES_H_ */
