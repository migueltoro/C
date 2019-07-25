/*
 * coordenadas_2d.h
 *
 *  Created on: 12 jul. 2019
 *      Author: migueltoro
 */

#ifndef COORDENADAS_H_
#define COORDENADAS_H_

#include "../types/types.h"
#include "../types/list.h"
#include "../types/accumulators.h"


typedef struct {
	double latitude;
	double longitude;
}coordenadas_2d;

coordenadas_2d coordenadas_2d_of(double latitude, double longitude);
coordenadas_2d coordenadas_2d_to_radians(coordenadas_2d c);
double coordenadas_2d_distance(coordenadas_2d c1, coordenadas_2d c2);
bool coordenadas_2d_cercanas(coordenadas_2d c1, coordenadas_2d c2, double d);
char * coordenadas_2d_tostring(coordenadas_2d * c1, const char * mem);
coordenadas_2d  coordenadas_2d_center(list lc);


typedef struct {
	double latitude;
	double longitude;
	double altitude;
}coordenadas_3d;

coordenadas_3d coordenadas_3d_of(double latitude, double longitude, double altitude);
double coordenadas_3d_distance(coordenadas_3d c1, coordenadas_3d c2);
char * coordenadas_3d_tostring(coordenadas_3d * c1, const char * mem);


#endif /* COORDENADAS_H_ */
