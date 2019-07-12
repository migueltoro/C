/*
 * preconditions.h
 *
 *  Created on: 10 jul. 2019
 *      Author: migueltoro
 */

#ifndef PRECONDITIONS_H_
#define PRECONDITIONS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void check_argument(bool condition, char * file, int line, char * message);
void * check_not_null(void * reference, char * file, int line, char * message);
int check_element_index(int index, int size, char * file, int line);
int check_position_index(int index, int size, char * file,int line);

#endif /* PRECONDITIONS_H_ */
