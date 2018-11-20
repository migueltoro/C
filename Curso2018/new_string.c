/*
 * more_string.c
 *
 *  Created on: 16 nov. 2018
 *      Author: migueltoro
 */


#include "new_string.h"

// string type

char * string_tostring(const void * e, char * mem) {
	char * a = (char *) e;
	return a;
}

long string_hashcode(const void * e) {
	char * a = (char *) e;
	return hash(a);
}

int string_equals(const void * e1, const void * e2) {
	char * a1 = (char *) e1;
	char * a2 = (char *) e2;
	return strcmp(a1, a2) == 0;
}

int string_naturalorder(const void * e1, const void * e2) {
	char * a1 = (char *) e1;
	char * a2 = (char *) e2;
	return strcmp(a1, a2);
}


char * remove_eol(char * string){
	int len = strlen(string);
	if (len>0) {
		string[len-1] = '\0';
	}
	return string;
}

char ** split(char * text, const char * delimiters, char ** tokens, int * ntokens){
	int i = 0;
	char * token = strtok(text,delimiters);
	while(token != NULL) {
//		printf("%s\n",token);
		tokens[i] = token;
		token = strtok(NULL,delimiters);
		i++;
	}
	*ntokens = i;
	return tokens;
}

void test_string(){
	char mem[256];
	char delimiters[] = " ,;.";
	char text[] = "El Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	char * tokens[100];
	int ntokens;
	split(text,delimiters,tokens,&ntokens);
	printf("%d\n",ntokens);
	for(int i =0;i<ntokens;i++){
		printf("%s\n",tokens[i]);
	}
	char te[] = "(3,4.7,-6)";
	int a;
	double b;
	int c;
	sscanf(te,"(%d,%lf,%d)",&a,&b,&c);
	printf("%d,%.2lf,%d\n",a,b,c);
	char pt[] = "(3.4,-7.9)";
	punto p = punto_parse(pt);
	printf("%s\n",punto_tostring(&p,mem));
	char pa[] = "(4,-9)";
	int_pair pp = int_pair_parse(pa);
	printf("%s\n",int_pair_tostring(&pp,mem));
	char tt2[] = "34 389 23.5 -37.90 (3,-5) (34.1,-67.8)";
	char delimiters2[] = " ";
	split(tt2,delimiters2,tokens,&ntokens);
	printf("%d\n",ntokens);
	for(int i =0;i<ntokens;i++){
		printf("%s\n",tokens[i]);
	}
	int a1 = int_parse(tokens[0]);
	long b1 = long_parse(tokens[1]);
	float c1 = float_parse(tokens[2]);
	double d1 = double_parse(tokens[3]);
	int_pair e1 = int_pair_parse(tokens[4]);
	punto f1 = punto_parse(tokens[5]);
	printf("%d,%ld,%f,%lf\n",a1,b1,c1,d1);
	printf("%s\n",int_pair_tostring(&e1,mem));
	printf("%s\n",punto_tostring(&f1,mem));
}

