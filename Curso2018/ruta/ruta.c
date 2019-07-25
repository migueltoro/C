/*
 * ruta.c
 *
 *  Created on: 14 jul. 2019
 *      Author: migueltoro
 */

#include "../ruta/ruta.h"

ruta * ruta_of_file(ruta * r, char * file){
	iterable i1 = file_iterable_pchar(file);
	iterable i2 = iterable_map(&i1,sizeof(marca),marca_parse);
	list ls = iterable_to_list(&i2,marca_type);
	r->marcas = ls;
	iterable_free(&i1);
	iterable_free(&i2);
	return r;
}

coordenadas_3d * marca_to_c3(coordenadas_3d * out, marca * in){
	*out = in->coordenadas;
	return out;
}

double * _f_dis(double * out, pair * in){
	coordenadas_3d c1 = ((marca *)in->key)->coordenadas;
	coordenadas_3d c2 = ((marca *)in->value)->coordenadas;
	*out = coordenadas_3d_distance(c1,c2);
	return out;
}

double ruta_longitud(ruta * r){
	double s = 0;
	for(int i =0; i<r->marcas.size-1;i++){
		coordenadas_3d c1 = ((marca *)list_get(&r->marcas,i))->coordenadas;
		coordenadas_3d c2 = ((marca *)list_get(&r->marcas,i+1))->coordenadas;
		s = s + coordenadas_3d_distance(c1,c2);
	}
	return s;
}

void ruta_printf(ruta * r){
	char mem[Tam_String];
	printf("\n");
	for(int i = 0; i < r->marcas.size; i++){
		printf("%s\n",list_get_string(&r->marcas,i,mem));
	}
}

double ruta_duracion(ruta * r){
	int size = list_size(&r->marcas);
	time_t initial_time = ((marca * )list_get(&r->marcas,0))->time;
	time_t last_time = ((marca *) list_get(&r->marcas,size-1))->time;
	return time_diff_hours(last_time,initial_time);
}

double ruta_velocidad_media(ruta * r) {
	return ruta_longitud(r)/ruta_duracion(r);
}

double ruta_velocidad_intervalo(ruta * r, int i) {
	time_t t0 = ((marca *) list_get(&r->marcas,i))->time;
	time_t t1 = ((marca *) list_get(&r->marcas,i+1))->time;
	coordenadas_3d c0 = ((marca *) list_get(&r->marcas,i))->coordenadas;
	coordenadas_3d c1 = ((marca *) list_get(&r->marcas,i+1))->coordenadas;
	double d = coordenadas_3d_distance(c0,c1);
	double time = time_diff_hours(t1,t0);
	return d/time;
}

coordenadas_2d * marca_to_c2(coordenadas_2d * out, marca * in){
	out->latitude = in->coordenadas.latitude;
	out->longitude = in->coordenadas.longitude;
	return out;
}

void test_ruta(){
	char mem[Tam_String];
	ruta r;
	ruta_of_file(&r,"ficheros/ruta.csv");
//	ruta_printf(&r);
	printf("\n________________\n");
	type nt = null_type;
	nt.size = sizeof(coordenadas_2d);
	list lc = list_map(&r.marcas,marca_to_c2,nt);
	coordenadas_2d c2 = coordenadas_2d_center(lc);
	printf("\nCentro de coordenadas en = %s\n",coordenadas_2d_tostring(&c2,mem));
	double rs = ruta_longitud(&r);
	printf("\nLongitud = %lf kilometros \n",rs);
	rs = ruta_duracion(&r);
	printf("\nDuración = %lf horas \n",rs);
	rs = ruta_velocidad_intervalo(&r,3);
	printf("\nVelocidad %lf km/h en intervalo 3\n",rs);
	rs = ruta_velocidad_media(&r);
	printf("\nVelocidad media = %lf km/h \n",rs);
}
