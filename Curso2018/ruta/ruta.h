/*
 * ruta.h
 *
 *  Created on: 14 jul. 2019
 *      Author: migueltoro
 */

#ifndef RUTA_H_
#define RUTA_H_

#include "../ruta/marca.h"
#include "../types/types.h"
#include "../types/iterables.h"
#include "../types/accumulators.h"

typedef struct{
	list marcas;
}ruta;

ruta * ruta_of_file(ruta * r, char * file);
double ruta_longitud(ruta * r);
double ruta_duracion(ruta * r);
char * ruta_tostring(ruta * r, char * mem);
double ruta_velocidad_intervalo(ruta * r, int i);
double ruta_velocidad_media(ruta * r);
void ruta_printf(ruta * r);
void test_ruta();
#endif /* RUTA_H_ */
