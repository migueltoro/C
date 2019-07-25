/*
 * palabras.h
 *
 *  Created on: 22 jul. 2019
 *      Author: migueltoro
 */

#ifndef PALABRAS_H_
#define PALABRAS_H_

#include "../types/iterables.h"
#include "../types/accumulators.h"

int numero_de_palabras(char * file);
hash_table frecuencias_de_palabras(char * file);

void test_palabras();

#endif /* PALABRAS_H_ */
