/*
 * files.c
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#include "files.h"

file_iterator open_file(char * file) {
	FILE * st = fopen(file,"r");
	assert(st != NULL && "no se encuentra el fichero");
	file_iterator itf = {st,false,false,""};
	return itf;
}

bool has_next_line(file_iterator * it) {
	if (!(it->is_done)) {
		char * r = fgets(it->next,Tam_String, it->file);
		if (r == NULL) {
			it->has_next = false;
		} else {
			it->has_next = true;
			int len = strlen(it->next);
			it->next[len-1] = '\0';
		}
		it->is_done = true;
	}
	return it->has_next;
}

char * next_line(file_iterator * it){
	it->is_done = false;
	return it->next;
}

