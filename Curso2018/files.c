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

void write_list_to_file(char * file, list * list, char * tostring(const void * source, char * mem)) {
	char mem[256];
	FILE * f = fopen(file, "wt");
	for (int i = 0; i < list->size; i++) {
		fprintf(f, "%s\n", tostring(list_get(list, i), mem));
	}
	fclose(f);
}

list lines(char * file){
	list r = list_empty();
	file_iterator f = open_file(file);
	while(has_next_line(&f)){
		char * s = next_line(&f);
		list_add(&r,s,Tam_String);
	}
	return r;
}

void test_files(){
	char mem[500];
	list ls = lines("prueba.txt");
	char * s1 = list_get(&ls,2);
	printf("s1 = %s\n", s1);
	char * s = list_tostring(&ls,string_tostring,mem);
	printf("ls1 = %s\n", s);
}

