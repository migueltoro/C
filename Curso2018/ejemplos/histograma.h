/*
 * recursivos.h
 *
 *  Created on: 19 dic. 2019
 *      Author: migueltoro
 */

#ifndef HISTOGRAMA_H_
#define HISTOGRAMA_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "../types/list.h"
#include "../types/types.h"

typedef struct {
	list * ls;
	int inf;
	int sup;
	int min_h;
	int min_index;
	int a;
} sol;

sol sol_zero();
sol sol_of(list * ls, int inf, int sup, int min_index);

#endif /* HISTOGRAMA_H_ */
