/*
 * basic_types.c
 *
 *  Created on: 13 ago. 2018
 *      Author: migueltoro
 */


#include "basic_types.h"




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

memory_heap types_memory = {0,0,NULL};

memory_heap * get_types_memory(){
	if(types_memory.elements == NULL) {
		types_memory = memory_heap_create();
	}
	return &types_memory;
}

void * get_mem_types(int size){
	return memory_heap_tam_memory(get_types_memory(),size);
}

void * get_value_types(int size, void * value){
	return memory_heap_memory_for_value(get_types_memory(),size, value);
}

void types_memory_clear(){
	memory_heap_free(&types_memory);
}


int type_equals(type * t1 , type * t2) {
	return !strcmp(t1->id,t2->id) && t1->size_type == t2->size_type;
}

type instance_type_1(type generic_type, type t1){
	assert(generic_type.num_type_parameters == 1 && "el tipo genérico debe tener un paraámtro de tipo solamente");
	type r = generic_type;
	r.types = get_mem_types(sizeof(type));
	r.types[0] = t1;
	return r;
}


type instance_type_2(type generic_type, type t1, type t2){
	assert(generic_type.num_type_parameters == 2 && "el tipo genérico debe tener dos paraámtros de tipo");
	type r = generic_type;
	r.types = get_mem_types(2*sizeof(type));
	r.types[0] = t1;
	r.types[1] = t2;
	return r;
}

type get_parameter_type(type generic_type, int index){
	assert(index >=0 && index < generic_type.num_type_parameters  && "indice fuera de rango");
	return generic_type.types[index];
}

char * tostring(type * type, char * mem, const void * e){
	return  type->tostring(type,mem,e);
}
long hashcode(type * type, const void * e){
	return type->hashcode(type,e);
}

int equals(type * type, const void * e1, const void * e2){
	return type->equals(type,e1,e2);
}

int naturalorder(type * type, const void * e1, const void * e2){
	return type->naturalorder(type,e1,e2);
}
void * pointer(type * type, const void * value, memory_heap * heap){
	return type->pointer(type,value,heap);
}

void * copy(type * type, void * target, const void * source){
	return type->copy(type,target,source);
}


// data type

char * data_tostring(char * mem, const void * e){
	data * d = (data *) e;
	return tostring(&d->type,mem,e);
}

long data_hashcode(const void * e){
	data * d = (data *) e;
	return hashcode(&d->type,e);
}

int data_equals(const void * e1, const void * e2){
	data * d1 = (data *) e1;
	data * d2 = (data *) e2;
	return type_equals(&d1->type,&d2->type) && equals(&d1->type,e1,e2);
}

int data_naturalorder(const void * e1, const void * e2){
	data * d1 = (data *) e1;
	data * d2 = (data *) e2;
	return naturalorder(&d1->type,d1,d2);
}

void * data_pointer(const void * value, memory_heap * heap){
	data * d = (data *) value;
	return pointer(&d->type,value,heap);
}

void * data_copy(void * target, const void * source){
	data * d1 = (data *) target;
	data * d2 = (data *) source;
	return copy(&d1->type,d1,d2);
}

// int type

char * int_tostring(type * type, char * mem, const void * e){
    int a = *(int *)e;
    sprintf(mem,"%d",a);
    return mem;
}

long int_hashcode(type * type, const void * e){
    int a = *(int *)e;
    char mem[256];
    sprintf(mem,"%d",a);
    return hash(mem);
}

int int_equals(type * type, const void * e1, const void * e2){
    int a = *(int *)e1;
    int b = *(int *)e2;
    return a == b;
}

int int_naturalorder(type * type, const void * e1,const  void * e2){
    int a = *(int *)e1;
    int b = *(int *)e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

void * int_pointer(type * type, const void * value, memory_heap * heap){
	int * element = (int *) malloc(sizeof(int));
	*element = *(int *)value;
	memory_heap_add(heap, element);
	return element;
}

void * int_copy(type * type, void * target, const void * source) {
	int * e_target = (int *) target;
	int * e_source = (int *) source;
	*e_target = *e_source;
	return e_target;
}
void * int_pointer_from_value(int a,memory_heap * heap) {
	int * element = (int *) malloc(sizeof(int));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}


type int_type = {0,NULL,sizeof(int),int_tostring,int_equals,int_hashcode,int_naturalorder,int_pointer,int_copy,"int_type"};

// long type

char * long_tostring(type * type, char * mem, const void * e){
    long a = *(long *)e;
    sprintf(mem,"%ld",a);
    return mem;
}

long long_hashcode(type * type, const void * e){
    long a = *(long *)e;
    char mem[256];
    sprintf(mem,"%ld",a);
    return hash(mem);
}

int long_equals(type * type, const void * e1,const  void * e2){
    long a = *(long *)e1;
    long b = *(long *)e2;
    return a == b;
}

int long_naturalorder(type * type, const void * e1,const  void * e2){
    long a = *(long *)e1;
    long b = *(long *)e2;
    long r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

void * long_pointer(type * type, const void * value, memory_heap * heap){
	long * element = (long *) malloc(sizeof(long));
	*element = *(long *)value;
	memory_heap_add(heap, element);
	return element;
}

void * long_copy(type * type, void * target, const void * source) {
	long * e_target = (long *) target;
	long * e_source = (long *) source;
	*e_target = *e_source;
	return e_target;
}


void * long_pointer_from_value(long a,memory_heap * heap) {
	long * element = (long *) malloc(sizeof(long));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}



type long_type = {0,NULL,sizeof(long),long_tostring,long_equals,long_hashcode,
		long_naturalorder,long_pointer, long_copy,"long_type"};


// float type

char * float_tostring(type * type, char * mem, const void * e){
    float a = *(float *)e;
    sprintf(mem,"%.2f",a);
    return mem;
}

long float_hashcode(type * type, const void * e){
    float a = *(float *)e;
    char mem[256];
    sprintf(mem,"%.2f",a);
    return hash(mem);
}

int float_equals(type * type, const void * e1, const void * e2){
    float a = *(float *)e1;
    float b = *(float *)e2;
    return a == b;
}

int float_naturalorder(type * type, const void * e1, const void * e2){
    float a = *(float *)e1;
    float b = *(float *)e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

void * float_pointer(type * type, const void * value, memory_heap * heap){
	float * element = (float *) malloc(sizeof(float));
	*element = *(float *)value;
	memory_heap_add(heap, element);
	return element;
}

void * float_copy(type * type, void * target, const void * source) {
	float * e_target = (float *) target;
	float * e_source = (float *) source;
	*e_target = *e_source;
	return e_target;
}

void * float_pointer_from_value(type * type, float a,memory_heap * heap) {
	float * element = (float *) malloc(sizeof(float));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}



type float_type = {0,NULL,sizeof(float),float_tostring,float_equals,float_hashcode,
		float_naturalorder,float_pointer, float_copy,"float_type"};

//double type

char * double_tostring(type * type, char * mem, const void * e){
    double a = *(double *)e;
    sprintf(mem,"%.2lf",a);
    return mem;
}


long double_hashcode(type * type, const void * e){
    double a = *(double *)e;
    char mem[256];
    sprintf(mem,"%.2lf",a);
    return hash(mem);
}

int double_equals(type * type, const void * e1, const void * e2){
    double a = *(double *)e1;
    double b = *(double *)e2;
    return a == b;
}

int double_naturalorder(type * type, const void * e1, const void * e2){
    double a = *(double *)e1;
    double b = *(double *)e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

void * double_pointer(type * type, const void * value, memory_heap * heap){
	double * element = (double *) malloc(sizeof(double));
	*element = *(double *)value;
	memory_heap_add(heap, element);
	return element;
}

void * double_copy(type * type, void * target, const void * source) {
	double * e_target = (double *) target;
	double * e_source = (double *) source;
	*e_target = *e_source;
	return e_target;
}

void * double_pointer_from_value(type * type, double a,memory_heap * heap) {
	double * element = (double *) malloc(sizeof(double));
	*element = a;
	memory_heap_add(heap, element);
	return element;
}



type double_type = {0,NULL,sizeof(double),double_tostring,double_equals,double_hashcode,
		double_naturalorder,double_pointer,double_copy,"double_type"};

// string type

char * string_tostring(type * type, char * mem, const void * e) {
	char * a = (char *) e;
	return a;
}

long string_hashcode(type * type, const void * e) {
	char * a = (char *) e;
	return hash(a);
}

int string_equals(type * type, const void * e1, const void * e2) {
	char * a1 = (char *) e1;
	char * a2 = (char *) e2;
	return strcmp(a1, a2) == 0;
}

int string_naturalorder(type * type, const void * e1, const void * e2) {
	char * a1 = (char *) e1;
	char * a2 = (char *) e2;
	return strcmp(a1, a2);
}

void * string_pointer(type * type, const void * value, memory_heap * heap){
	char * element = (char *) malloc(Tam_String);
	strcpy(element,value);
	memory_heap_add(heap, element);
	return element;
}

void * string_copy(type * type, void * target, const void * source) {
	char * e_target = (char *) target;
	char * e_source = (char *) source;
	strcpy(e_target,e_source);
	return e_target;
}


char * remove_eol(char * string){
	int len = strlen(string);
	if (len>0) {
		string[len-1] = '\0';
	}
	return string;
}

type string_type = {0,NULL,Tam_String, string_tostring,string_equals, string_hashcode,
		string_naturalorder,string_pointer,string_copy,"string_type" };

// tuple2 type


char * tuple2_tostring(type * type, char * mem, const void * t) {
	char nmkey[256];
	char nmvalue[256];
	tuple2 tuple = *(tuple2 *)t;
	sprintf(mem,"(%s,%s)",
			type->types[0].tostring(&type->types[0],nmkey,tuple.key),
			type->types[1].tostring(&type->types[1],nmvalue,tuple.value));
    return mem;
}

int tuple2_equals(type * type, const void * t1, const void * t2){
	tuple2 tt1 = *(tuple2 *)t1;
	tuple2 tt2 = *(tuple2 *)t2;
	return  type->types[0].equals(&type->types[0],tt1.key,tt2.key)
			&& type->types[1].equals(&type->types[1],tt1.value,tt2.value);
}

long tuple2_hashcode(type * type, const void * t) {
	tuple2 tt = *(tuple2 *)t;
    return hashcode(&type->types[0],t)*31+hashcode(&type->types[1],tt.value);
}

int tuple2_naturalorder(type * type, const void * t1, const void * t2) {
	tuple2 tt1 = *(tuple2 *)t1;
	tuple2 tt2 = *(tuple2 *)t2;
	int r;
	r = naturalorder(&type->types[0],tt1.key,tt2.key);
	if(r == 0) r = naturalorder(&type->types[1],tt1.value,tt2.value);
	return r;
}

void * tuple2_pointer(type * type, const void * value, memory_heap * heap){
	tuple2 * element = (tuple2 *) malloc(sizeof(tuple2));
	*element = *(tuple2 *)value;
	memory_heap_add(heap, element);
	return element;
}

void * tuple2_copy(type * type, void * target, const void * source) {
	tuple2 * e_target = (tuple2 *) target;
	tuple2 * e_source = (tuple2 *) source;
	*e_target = *e_source;
	return e_target;
}


type tuple2_type = {2,NULL,sizeof(tuple2),tuple2_tostring,tuple2_equals,tuple2_hashcode,
		tuple2_naturalorder,tuple2_pointer,tuple2_copy,"tuple2_type"};


//optional type

char * optional_tostring(type * type, char * mem, const void * e){
	optional op = *(optional *)e;
	if(op.value == NULL) sprintf(mem,"_");
	else sprintf(mem,"%s",tostring(&type->types[0],mem,op.value));
	return mem;
}

int optional_equals(type * type, const void * e1, const void * e2){
	optional op1 = *(optional *)e1;
	optional op2 = *(optional *)e2;
	return (op1.value == NULL && op2.value == NULL) ||
			equals(&type->types[0],op1.value,op2.value);
}

long optional_hashcode(type * type, const void * e){
	optional op = *(optional *)e;
	return hashcode(&type->types[0],op.value);
}

int optional_naturalorder(type * type, const void * e1,const  void * e2) {
	optional op1 = *(optional *)e1;
	optional op2 = *(optional *)e2;
	int r;
	if(op1.value == NULL && op2.value == NULL) r = 0;
	else if(op1.value == NULL) r= 1;
	else if(op2.value == NULL) r = -1;
	else r = type->types[0].naturalorder(&type->types[0],op1.value,op2.value);
	return r;
}

void * optional_pointer(type * type, const void * value, memory_heap * heap){
	optional * element = (optional *) malloc(sizeof(optional));
	*element = *(optional *)value;
	memory_heap_add(heap, element);
	return element;
}

void * optional_copy(type * type, void * target, const void * source) {
	type->types[0].copy(&type->types[0],target,source);
	return target;
}


type optional_type = {1,NULL,sizeof(optional),optional_tostring,optional_equals,optional_hashcode,
		optional_naturalorder,optional_pointer,optional_copy,"optional_type"};

// void * type

type void_star_type = {0,NULL,sizeof(void *),NULL,NULL,NULL,NULL,NULL,NULL,"void_star_type"};

// unkown type

type unkown_type = {0,NULL,sizeof(void *),NULL,NULL,NULL,NULL,NULL,NULL,"unkown_type"};


double punto_distancia_al_origen(const punto p){
	double x2 = p.x*p.x;
	double y2 = p.y*p.y;
	return sqrt(x2+y2);
}

char * punto_tostring(type * type, char * mem, const void * p){
	punto np = *(punto *)p;
	sprintf(mem,"(%lf,%lf)",np.x,np.y);
	return mem;
}

int punto_equals(type * type, const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	return np1.x == np2.x && np1.y == np2.y;
}

long punto_hashcode(type * type, const void * p){
	char mem[256];
	char * s = punto_tostring(type,mem,p);
	return hash(s);
}

int punto_naturalorder(type * type, const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	double d1 = punto_distancia_al_origen(np1);
	double d2 = punto_distancia_al_origen(np2);
	return naturalorder(&double_type,&d1,&d2);
}

void * punto_pointer(type * type, const void * value, memory_heap * heap){
	punto * element = (punto *) malloc(sizeof(punto));
	*element = *(punto *)value;
	memory_heap_add(heap, element);
	return element;
}

void * punto_copy(type * type, void * target, const void * source) {
	punto * e_target = (punto *) target;
	punto * e_source = (punto *) source;
	*e_target = *e_source;
	return e_target;
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

type punto_type = {0,NULL,sizeof(punto), punto_tostring,punto_equals, punto_hashcode,
		punto_naturalorder,punto_pointer,punto_copy,"punto_type" };
