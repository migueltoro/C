/*
 * types.c
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#include "types.h"

/* Hash a string */
unsigned long int hash(const char *key) {

	unsigned long int hashval = 0 ;
	int i = 0;
	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 5;
		hashval += key[ i ];
		i++;
	}
	return hashval;
}



// int type

int int_parse(char * text){
	int p;
	sscanf(text,"%d",&p);
	return p;
}

char * int_tostring(const void * e, char * mem){
    int a = *(int *)e;
    sprintf(mem,"%d",a);
    return mem;
}

long int_hashcode(const void * e){
    int a = *(int *)e;
    char mem[256];
    sprintf(mem,"%d",a);
    return hash(mem);
}

int int_equals(const void * e1, const void * e2){
    int a = *(int *)e1;
    int b = *(int *)e2;
    return a == b;
}

int int_naturalorder(const void * e1,const  void * e2){
    int a = *(int *)e1;
    int b = *(int *)e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

// long type

long long_parse(char * text){
	long p;
	sscanf(text,"%ld",&p);
	return p;
}

char * long_tostring(const void * e, char * mem){
    long a = *(long *)e;
    sprintf(mem,"%ld",a);
    return mem;
}

long long_hashcode(const void * e){
    long a = *(long *)e;
    char mem[256];
    sprintf(mem,"%ld",a);
    return hash(mem);
}

int long_equals(const void * e1,const  void * e2){
    long a = *(long *)e1;
    long b = *(long *)e2;
    return a == b;
}

int long_naturalorder(const void * e1,const  void * e2){
    long a = *(long *)e1;
    long b = *(long *)e2;
    long r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

// float type

float float_parse(char * text){
	float p;
	sscanf(text,"%f",&p);
	return p;
}

char * float_tostring(const void * e, char * mem){
    float a = *(float *)e;
    sprintf(mem,"%.2f",a);
    return mem;
}

long float_hashcode(const void * e){
    float a = *(float *)e;
    char mem[256];
    sprintf(mem,"%.2f",a);
    return hash(mem);
}

int float_equals(const void * e1, const void * e2){
    float a = *(float *)e1;
    float b = *(float *)e2;
    return a == b;
}

int float_naturalorder(const void * e1, const void * e2){
    float a = *(float *)e1;
    float b = *(float *)e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}


//double type

double double_parse(char * text){
	double p;
	sscanf(text,"%lf",&p);
	return p;
}

char * double_tostring(const void * e, char * mem){
    double a = *(double *)e;
    sprintf(mem,"%0.2lf",a);
    return mem;
}


long double_hashcode(const void * e){
    double a = *(double *)e;
    char mem[256];
    sprintf(mem,"%.2lf",a);
    return hash(mem);
}

int double_equals(const void * e1, const void * e2){
    double a = *(double *)e1;
    double b = *(double *)e2;
    return a == b;
}

int double_naturalorder(const void * e1, const void * e2){
    double a = *(double *)e1;
    double b = *(double *)e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

int_pair int_pair_parse(char * text){
	int_pair p;
	sscanf(text,"(%d,%d)",&p.a,&p.b);
	return p;
}

char * int_pair_tostring(const void * p, char * mem){
	int_pair np = *(int_pair *)p;
	sprintf(mem,"(%d,%d)",np.a,np.b);
	return mem;
}

int int_pair_equals(const void * p1, const void * p2){
	int_pair np1 = *(int_pair *)p1;
	int_pair np2 = *(int_pair *)p2;
	return np1.a == np2.a && np1.b == np2.b;
}

long int_pair_hashcode(const void * p){
	char mem[256];
	char * s = int_pair_tostring(p,mem);
	return hash(s);
}

int int_pair_naturalorder(const void * p1, const void * p2){
	int_pair np1 = *(int_pair *)p1;
	int_pair np2 = *(int_pair *)p2;
	int r  = int_naturalorder(&np1.a,&np2.a);
	if(r==0) r  = int_naturalorder(&np1.b,&np2.b);
	return r;
}


Cuadrante punto_cuadrante(const punto p) {
	Cuadrante r;
	if(p.x >=0 && p.y>=0){
		r = PRIMERO;
	} else if(p.x < 0 && p.y>=0) {
		r = SEGUNDO;
	} else if(p.x < 0 && p.y<0) {
		r = TERCERO;
	} else {
		r = CUARTO;
	}
	return r;
}

punto punto_parse(char * text){
	punto pt;
	sscanf(text,"(%lf,%lf)",&pt.x,&pt.y);
	return pt;
}

double punto_distancia_al_origen(const punto p){
	double x2 = p.x*p.x;
	double y2 = p.y*p.y;
	return sqrt(x2+y2);
}

char * punto_tostring(const void * p, char * mem){
	punto np = *(punto *)p;
	sprintf(mem,"(%lf,%lf)",np.x,np.y);
	return mem;
}



int punto_equals(const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	return np1.x == np2.x && np1.y == np2.y;
}

long punto_hashcode(const void * p){
	char mem[256];
	char * s = punto_tostring(p,mem);
	return hash(s);
}

int punto_naturalorder(const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	double d1 = punto_distancia_al_origen(np1);
	double d2 = punto_distancia_al_origen(np2);
	return double_naturalorder(&d1,&d2);
}


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

