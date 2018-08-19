/*
 * basic_types.c
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */


#include "basic_types.h"
#include "memory_heap.h"

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

int type_equals(const type t1 , const type t2) {
	return !strcmp(t1.id,t2.id) && t1.size == t2.size;
}

// int type

char * int_tostring(char * mem, const void * e){
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

type int_type = {sizeof(int),int_tostring,int_equals,int_hashcode,int_naturalorder,"int_type"};

// long type

char * long_tostring(char * mem, const void * e){
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

type long_type = {sizeof(long),long_tostring,long_equals,long_hashcode,long_naturalorder,"long_type"};


// float type

char * float_tostring(char * mem, const void * e){
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

type float_type = {sizeof(float),float_tostring,float_equals,float_hashcode,float_naturalorder,"float_type"};

//double type

char * double_tostring(char * mem, const void * e){
    double a = *(double *)e;
    sprintf(mem,"%.2lf",a);
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

type double_type = {sizeof(double),double_tostring,double_equals,double_hashcode,double_naturalorder,"double_type"};

// string type

char * string_tostring(char * mem, const void * e) {
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

type string_type = { 256, string_tostring,string_equals, string_hashcode,
		string_naturalorder,"string_type" };

// tuple2 type

char * tuple2_tostring(char * mem, const void * t) {
	char nmkey[256];
	char nmvalue[256];
	tuple2 tuple = *(tuple2 *)t;
	sprintf(mem,"(%s,%s)",tuple.key_type.tostring(nmkey,tuple.key), tuple.value_type.tostring(nmvalue,tuple.value));
    return mem;
}

int tuple2_equals(const void * t1, const void * t2){
	tuple2 tt1 = *(tuple2 *)t1;
	tuple2 tt2 = *(tuple2 *)t2;
	return  type_equals(tt1.key_type,tt2.key_type)
			&& type_equals(tt1.value_type,tt2.value_type)
			&& tt1.key_type.equals(tt1.key,tt2.key)
			&& tt1.value_type.equals(tt1.value,tt2.value);
}
long tuple2_hashcode(const void * t) {
	tuple2 tt = *(tuple2 *)t;
    return tt.key_type.hashcode(tt.key)*31+tt.value_type.hashcode(tt.value);
}

int tuple2_naturalorder(const void * t1, const void * t2) {
	tuple2 tt1 = *(tuple2 *)t1;
	tuple2 tt2 = *(tuple2 *)t2;
	int r;
	r = tt1.key_type.naturalorder(tt1.key,tt2.key);
	if(r == 0) r = tt1.value_type.naturalorder(tt1.value,tt2.value);
	return r;
}


type tuple2_type = {sizeof(tuple2),tuple2_tostring,tuple2_equals,
		tuple2_hashcode,tuple2_naturalorder,"tuple2_type"};


//optional type

char * optional_tostring(char * mem, const void * e){
	optional op = *(optional *)e;
	if(op.value == NULL) sprintf(mem,"_");
	else sprintf(mem,"%s",op.type.tostring(mem,op.value));
	return mem;
}

int optional_equals(const void * e1, const void * e2){
	optional op1 = *(optional *)e1;
	optional op2 = *(optional *)e2;
	return (type_equals(op1.type,op2.type)  && (op1.value == NULL && op2.value == NULL)) ||
			op1.type.equals(op1.value,op2.value);
}
long optional_hashcode(const void * e){
	optional op = *(optional *)e;
	return op.type.hashcode(op.value);
}

int optional_naturalorder(const void * e1,const  void * e2) {
	optional op1 = *(optional *)e1;
	optional op2 = *(optional *)e2;
	assert(type_equals(op1.type,op2.type));
	int r;
	if(op1.value == NULL && op2.value == NULL) r = 0;
	else if(op1.value == NULL) r= 1;
	else if(op2.value == NULL) r = -1;
	else r = op1.type.naturalorder(op1.value,op2.value);
	return r;
}

type optional_type = {sizeof(optional),optional_tostring,optional_equals,
		optional_hashcode,optional_naturalorder,"optional_type"};

// void * type

type void_star_type = {sizeof(void *),NULL,NULL,NULL,NULL,"void_star_type"};

// unkown type

type unkown_type = {sizeof(void *),NULL,NULL,NULL,NULL,"unkown_type"};


double punto_distancia_al_origen(const punto p){
	double x2 = p.x*p.x;
	double y2 = p.y*p.y;
	return sqrt(x2+y2);
}

char * punto_tostring(char * mem, const void * p){
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
	char * s = punto_tostring(mem,p);
	return hash(s);
}

int punto_naturalorder(const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	double d1 = punto_distancia_al_origen(np1);
	double d2 = punto_distancia_al_origen(np2);
	return double_type.naturalorder(&d1,&d2);
}

Cuadrante pt_cuadrante(const punto p) {
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

type punto_type = {sizeof(punto), punto_tostring,punto_equals, punto_hashcode,
		punto_naturalorder,"punto_type" };
