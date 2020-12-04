/*
 * tupla.h
 *
 *  Created on: 30 nov. 2020
 *      Author: migueltoro
 */

#ifndef TUPLA_H_
#define TUPLA_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../types/types.h"


typedef struct {
	int li;
	int ls;
	int suma;
}smax;

smax smax_of(int li,int ls,int suma);
int * smax_parse(smax * out, char * text);
char * smax_tostring(const smax * e, char * mem);
bool smax_equals(const smax * e1, const smax * e2);
int smax_naturalorder(const smax * e1,const smax * e2);

extern type smax_type;

#endif /* TUPLA_H_ */
