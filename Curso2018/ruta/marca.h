/*
 * marca.h
 *
 *  Created on: 12 jul. 2019
 *      Author: migueltoro
 */

#ifndef MARCA_H_
#define MARCA_H_

#include "../types/types.h"
#include "../types/dates.h"
#include "../types/list.h"
#include "../types/iterables.h"
#include "../types/accumulators.h"
#include "../data/coordenadas.h"


typedef struct {
	time_t time;
	coordenadas_3d coordenadas;
}marca;

marca marca_of(time_t time, coordenadas_3d coordenadas);
marca * marca_parse(marca * out, const char * in);
char * marca_tostring(marca * m, char * mem);

bool marca_equals(const marca * e1, const marca * e2);
int marca_naturalorder(const marca * e1, const marca * e2);


extern type marca_type;

void test_marca();
#endif /* MARCA_H_ */
