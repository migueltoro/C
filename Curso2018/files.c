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

punto_list list_punto_from_file(char * file) {
	punto_list r7 = empty_punto_list(200);
	file_iterator f  = open_file("prueba.txt");
	while (has_next_line(&f)) {
		assert(r7.size < r7.tam);
		char * line = next_line(&f);
		double x;
		double y;
		sscanf(line, "%lf,%lf", &x, &y);
		r7.data[r7.size].x = x;
		r7.data[r7.size].y = y;
		r7.size = r7.size + 1;
	}
	return r7;
}

void problema59(char * file,long n){
	long i = 2;
	FILE * st = fopen(file,"w");
	assert(st != NULL && "no se encuentra el fichero");
	while(i<n){
		fprintf(st,"%ld\n",i);
		i = siguiente_primo(i);
	}
	fclose(st);
}
