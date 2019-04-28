/*
 * ejemplos.h
 *
 *  Created on: 19 nov. 2018
 *      Author: migueltoro
 */

#ifndef EJEMPLOS_H_
#define EJEMPLOS_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "alist.h"
#include "types.h"
#include "hash_table.h"
#include "files.h"
#include "memory_heap.h"

double n_problema1(alist ls);

alist n_problema2(alist ls);

bool n_problema3(alist ls, bool (*p)(int e));

bool n_problema4(alist ls, bool (*p)(int e));

int n_problema5(alist ls);

double n_problema6(alist ls, double umbral);

punto * n_problema8(alist ls, int (*cmp)(const void *, const void *));

hash_table n_problema11(alist ls);

alist n_problema61(char * file);

void n_problema59(char * file,long n);

void test_ejemplos();

#endif /* EJEMPLOS_H_ */
