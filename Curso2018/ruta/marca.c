/*
 * marca.c
 *
 *  Created on: 12 jul. 2019
 *      Author: migueltoro
 */

#include "../ruta/marca.h"

marca marca_of(time_t time, coordenadas_3d coordenadas){
	marca m  = {time,coordenadas};
	return m;
}


marca * marca_parse(marca * out, const char * in) {
	int n = strlen(in);
	char cp[n+2];
	strcpy(cp,in);
	char * campos[4];
	int nc = 0;
	char * tok = strtok(cp,",");
	while(tok!=NULL){
		campos[nc] = tok;
		tok = strtok(NULL,",");
		nc++;
	}
	char mens[Tam_String];
	sprintf(mens,"numero de campos %d",nc);
	check_argument(nc==4,__FILE__,__LINE__,mens);
	marca m;
	m.time = time_parse_hour(campos[0]);
	coordenadas_3d coordenadas = coordenadas_3d_of(
			double_parse_s(campos[1]),
			double_parse_s(campos[2]),
			double_parse_s(campos[3]) / 1000);
	m.coordenadas = coordenadas;
	*out = m;
	return out;
}

char * marca_tostring(marca * m, char * mem){
	char mr1[Tam_String];
	char mr2[Tam_String];
	sprintf(mem,"(%s,%s)",time_hours_tostring(&m->time,mr1),coordenadas_3d_tostring(&m->coordenadas,mr2));
	return mem;
}

bool marca_equals(const marca * e1, const marca * e2){
	return time_equals(e1->time,e2->time);
}

int marca_naturalorder(const marca * e1, const marca * e2){
	return time_naturalorder(e1->time,e2->time);
}

type marca_type = {marca_equals,marca_tostring,marca_naturalorder,marca_parse,sizeof(marca)};

void test_marca() {
	char mem[250];
	char in[] =	"00:02:36, 36.75061631016433,-5.148278838023543,715.4000244140625";
	marca m;
	marca_parse(&m, in);
	printf("9: %s\n", marca_tostring(&m, mem));
}
