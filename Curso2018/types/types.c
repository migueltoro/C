/*
 * types.c
 *
 *  Created on: 4 nov. 2018
 *      Author: migueltoro
 */

#include "../types/types.h"

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

unsigned long int hash_code(void * in, type t){
	char mem[256];
	char * r = t.tostring(in, mem);
	unsigned long int hash_index = hash(r);
	return hash_index;
}

// int type

int int_parse_s(char * text){
	int p;
	sscanf(text,"%d",&p);
	return p;
}

int * int_parse(int * out, char * text){
	sscanf(text,"%d",out);
	return out;
}

char * int_tostring(const int * e, char * mem){
    sprintf(mem,"%d",*e);
    return mem;
}

bool int_equals(const int * e1, const int * e2){
    return *e1 == *e2;
}

int int_naturalorder(const int * e1,const int * e2){
    int a = *e1;
    int b = *e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}


type int_type = {int_equals,int_tostring,int_naturalorder,int_parse,sizeof(int)};

// long type

long long_parse_s(char * text){
	long p;
	sscanf(text,"%ld",&p);
	return p;
}

long * long_parse(long * out, char * text){
	sscanf(text,"%ld",out);
	return out;
}

char * long_tostring(const long * e, char * mem){
    sprintf(mem,"%ld",*e);
    return mem;
}

bool long_equals(const long * e1,const long * e2){
    return *e1 == *e2;
}

int long_naturalorder(const long * e1,const long * e2){
    long a = *e1;
    long b = *e2;
    long r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}


type long_type = {long_equals,long_tostring,long_naturalorder,long_parse,sizeof(long)};

// float type

float float_parse_s(char * text){
	float p;
	sscanf(text,"%f",&p);
	return p;
}

float * float_parse(float * out, char * text){
	sscanf(text,"%f",out);
	return out;
}

char * float_tostring(const float * e, char * mem){
    sprintf(mem,"%.2f",*e);
    return mem;
}

bool float_equals(const float * e1, const float * e2){
    return *e1 == *e2;
}

int float_naturalorder(const float * e1, const float * e2){
    float a = *e1;
    float b = *e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}

type float_type = {float_equals,float_tostring,float_naturalorder,float_parse,sizeof(float)};

//double type

double double_parse_s(char * text){
	double p;
	sscanf(text,"%lf",&p);
	return p;
}

double * double_parse(double * out, char * text){
	sscanf(text,"%lf",out);
	return out;
}

char * double_tostring(const double * e, char * mem){
    sprintf(mem,"%0.2lf",*e);
    return mem;
}

bool double_equals(const double * e1, const double * e2){
    return *e1 == *e2;
}

int double_naturalorder(const double * e1, const double * e2){
    double a = *e1;
    double b = *e2;
    int r;
    if(a==b) r = 0;
    else if(a<b) r = -1;
    else r = +1;
    return r;
}


type double_type = {double_equals,double_tostring,double_naturalorder,double_parse,sizeof(double)};

// int_pair

int_pair int_pair_parse_s(char * text){
	int_pair p;
	sscanf(text,"(%d,%d)",&p.a,&p.b);
	return p;
}

int_pair * int_pair_parse(int_pair * out, char * text){
	sscanf(text,"(%d,%d)",&out->a,&out->b);
	return out;
}

char * int_pair_tostring(const int_pair * p, char * mem){
	sprintf(mem,"(%d,%d)",p->a,p->b);
	return mem;
}

bool int_pair_equals(const int_pair * p1, const int_pair * p2){
	return p1->a == p2->a && p1->b == p2->b;
}

int int_pair_naturalorder(const int_pair * p1, const int_pair * p2){
	int_pair np1 = *p1;
	int_pair np2 = *p2;
	int r  = int_naturalorder(&np1.a,&np2.a);
	if(r==0) r  = int_naturalorder(&np1.b,&np2.b);
	return r;
}


type int_pair_type = {int_pair_equals,int_pair_tostring,int_pair_naturalorder,int_pair_parse,sizeof(int_pair)};

Cuadrante punto_cuadrante(const punto * p) {
	Cuadrante r;
	if(p->x >=0 && p->y>=0){
		r = PRIMERO;
	} else if(p->x < 0 && p->y>=0) {
		r = SEGUNDO;
	} else if(p->x < 0 && p->y<0) {
		r = TERCERO;
	} else {
		r = CUARTO;
	}
	return r;
}

punto punto_parse_s(char * text){
	punto pt;
	sscanf(text,"(%lf,%lf)",&pt.x,&pt.y);
	return pt;
}

punto * punto_parse(punto * out, char * text){
	sscanf(text,"(%lf,%lf)",&out->x,&out->y);
	return out;
}

double punto_distancia_al_origen(const punto * p){
	double x2 = p->x*p->x;
	double y2 = p->y*p->y;
	return sqrt(x2+y2);
}

char * punto_tostring(const punto * p, char * mem){
	sprintf(mem,"(%.2lf,%.2lf)",p->x,p->y);
	return mem;
}

bool punto_equals(const punto * p1, const punto * p2){
	return p1->x == p2->x && p1->y == p2->y;
}

int punto_naturalorder(const punto * p1, const punto * p2){
	double d1 = punto_distancia_al_origen(p1);
	double d2 = punto_distancia_al_origen(p2);
	return double_naturalorder(&d1,&d2);
}

type punto_type = {punto_equals,punto_tostring,punto_naturalorder,punto_parse,sizeof(punto)};

// pair

void * pair_to_key(void * out, pair * in){
	return in->key;
}

void * pair_to_value(void * out, pair * in){
	return in->value;
}

// pair type

pair_t * pair_t_parse(pair_t * out, char * text){
	char k[Tam_String];
	char v[Tam_String];
	sscanf(text,"(%s,%s)",k,v);
	out->key_type->parse(out->key,k);
	out->value_type->parse(out->value,v);
	return out;
}

char * pair_t_tostring(const pair_t * e, char * mem){
	char m1[Tam_String];
	char m2[Tam_String];
	char * key = e->key_type->tostring(e->key,m1);
	char * value = e->value_type->tostring(e->value,m2);
	sprintf(mem,"(%s,%s)",key,value);
	return mem;
}

bool pair_t_equals(const pair_t * e1, const pair_t * e2){
	return e1->key_type->equals(e1->key,e2->key) &&
		   e1->value_type->equals(e1->value,e2->value);
}

int pair_t_naturalorder(const pair_t * e1, const pair_t * e2){
	int r = e1->key_type->order(e1->key,e2->key);
	if(r==0) r = e2->value_type->order(e1->value,e2->value);
	return r;
}


pair_t pair_t_of(pair * p, type * t1, type * t2){
	pair_t r = {p->key,p->value,t1,t2};
	return r;
}

pair_t pair_t_of_2(void * key, void * value, type * t1, type * t2){
	pair_t r = {key,value,t1,t2};
	return r;
}

type pair_type = {pair_t_equals,pair_t_tostring,pair_t_naturalorder,pair_t_parse,sizeof(pair_t)};

// string type

#define INITIAL_TAM 250
#define INC_TAM 500


string string_empty(){
	void * data = malloc(INITIAL_TAM);
	string st = {INITIAL_TAM,0,data};
	strcpy(st.data,"");
	return st;
}

bool string_is_empty(string * in){
	return strlen(in->data) == 0;
}

bool string_not_is_empty(string * in){
	return strlen(in->data) > 0;
}

string string_of_pchar(const char * initial){
	string bf = string_empty();
	string_add_pchar(&bf,initial);
	return bf;
}

void * string_add_pchar(string * out, const char * s) {
	check_not_null(s,__FILE__,__LINE__,"Cadena null");
	int n = strlen(s);
	if(out->size+n>out->tam){
		int tm = MAX(out->size+n,out->tam+INC_TAM);
		out->data = realloc(out->data,tm);
		check_not_null(out->data,__FILE__,__LINE__,"No ha sido posible aumentar la memoria");
		out->tam = tm;
	}
	if(out->size == 0) strcpy(out->data,s);
	else strcat(out->data,s);
	out->size = out->size +n;
	return out->data;
}

void * string_add_string(string * out, const string * in) {
	return string_add_pchar(out,in->data);
}

void string_clear(string * in){
	free(in->data);
	void * data = malloc(INITIAL_TAM);
	in->tam = INITIAL_TAM;
	in->size = 0;
	in->data = data;
	strcpy(in->data,"");
}

void string_free(string * in){
	string * st = (string * ) in;
	free(st->data);
}

string * string_parse(string * out, char * text){
	string_add_pchar(out,text);
	return out;
}

char * string_tostring(const string * e, char * mem) {
	strcpy(mem,e->data);
	return mem;
}

bool string_equals(const string * e1, const string * e2) {
	return strcmp(e1->data, e2->data) == 0;
}

int string_naturalorder(const string * e1, const string * e2) {
	return strcmp(e1->data, e2->data);
}

type string_type = {string_equals,string_tostring,string_naturalorder,string_parse,sizeof(string)};


// pchar type

char * remove_eol_s(char * in){
	int len = strlen(in);
	if (len>0 && in[len-1] == 10) {
		in[len-1] = '\0';
	}
	return in;
}

char *  remove_eol(char * out, char * in){
	strcpy(out,in);
	remove_eol_s(out);
	return out;
}

int split_text(const char * in, const char * delimiters, char ** tokens){
	int i = 0;
	char * token = strtok(in,delimiters);
	while(token != NULL) {
		tokens[i] = token;
		token = strtok(NULL,delimiters);
		i++;
	}
	return i;
}

char * pchar_parse(char * out, char * text){
	return text;
}
char * pchar_tostring(const char * e, char * mem){
	strcpy(mem,e);
	return mem;
}
bool pchar_equals(const char * e1, const char * e2){
	return strcmp(e1,e2) == 0;
}

int pchar_naturalorder(const char * e1,const char * e2){
	return strcmp(e1,e2);
}

type pchar_type = {pchar_equals,pchar_tostring,pchar_naturalorder,pchar_parse,Tam_String};

bool pchar_is_empty(char * in){
	return strlen(in) == 0;
}
bool pchar_not_is_empty(char * in){
	return strlen(in) > 0;
}
bool pchar_all_space(char * in){
	bool r = true;
	int i =0;
	while(in[i] != '\0') {
		r = isspace(in[i]);
		if(!r) break;
		i=i+1;
	}
	return r;
}
bool pchar_not_all_space(char * in){
	return !pchar_all_space(in);
}

// optional type

optional * optional_parse(optional * out, char * text){
	out->type->parse(out->value,text);
	return out;
}
char * optional_tostring(const optional * e, char * mem){
	if(e->value == NULL){
		strcpy(mem,"null");
	} else {
		e->type->tostring(e->value,mem);
	}
	return mem;
}
bool optional_equals(const optional * e1, const optional * e2){
	return e1->type->equals(e1->value,e2->value);
}
int optional_naturalorder(const optional * e1, const optional * e2){
	return e1->type->order(e1->value,e2->value);
}


optional optional_of(void * in, type * type){
	optional r = {in,type};
	return r;
}

type optional_type = {optional_equals,optional_tostring,optional_naturalorder,optional_parse,sizeof(optional)};

// null type

type null_type = {NULL,NULL,NULL,NULL,0};

// utilities

void * copy(void * out, void * in, int size){
	check_not_null(in,__FILE__,__LINE__,"puntero null");
	check_not_null(out,__FILE__,__LINE__,"puntero null");
	memcpy(out,in,size);
	return out;
}

void * copy_in_pointer(void ** out, void * in, int size){
	check_not_null(in,__FILE__,__LINE__,"puntero null");
	check_not_null(out,__FILE__,__LINE__,"puntero null");
	void * r = *out;
	memcpy(r,in,size);
	return out;
}

void * copy_and_mem(void * in, int size) {
	check_not_null(in, __FILE__, __LINE__, "puntero null");
	if (size == 0) return NULL;
	void * element = (void *) malloc(size);
	memcpy(element, in, size);
	return element;
}

void * swap(void * out, void * in, int size){
	check_not_null(in,__FILE__,__LINE__,"puntero null");
	check_not_null(out,__FILE__,__LINE__,"puntero null");
	check_argument(size>0,__FILE__,__LINE__,"size debe ser mayor que cero");
	void * tmp = malloc(size);
	memcpy(tmp,in,size);
	memcpy(in,out,size);
	memcpy(out,tmp,size);
	free(tmp);
	return out;
}

void * reduce_one_indirection(void * in){
	void ** r = (void **) in;
	void * out = * r;
	return out;
}


void test_string(){
	char mem[256];
	char delimiters[] = " ,;.";
	char text[600] = "El Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las    negociaciones de la ministra María Jesús Montero. ";
	char * tokens[100];
	int n = split_text(text, delimiters,tokens);
	printf("1: %d\n",n);
	for(int i =0;i<n;i++){
		printf("2: %d,%s\n",i,tokens[i]);
	}
	char te[] = "(3,4.7,-6)";
	int a;
	double b;
	int c;
	sscanf(te,"(%d,%lf,%d)",&a,&b,&c);
	printf("3: %d,%.2lf,%d\n",a,b,c);
	char pt[] = "(3.4,-7.9)";
	punto p = punto_parse_s(pt);
	printf("4: %s\n",punto_tostring(&p,mem));
	char pa[] = "(4,-9)";
	int_pair pp = int_pair_parse_s(pa);
	printf("5: %s\n",int_pair_tostring(&pp,mem));
	char tt2[200] = "34 389   23.5 -37.90 (3,-5) (34.1,-67.8)";
	char delimiters2[] = " ";
	char * tt[10];
	n = split_text(tt2,delimiters2,tt);
	printf("6: %d\n",n);
	for(int i =0;i<n;i++){
		printf("%d,%s\n",i,tt[i]);
	}
	int a1 = int_parse_s(tt[0]);
	long b1 = long_parse_s(tt[1]);
	float c1 = float_parse_s(tt[2]);
	double d1 = double_parse_s(tt[3]);
	int_pair e1 = int_pair_parse_s(tt[4]);
	punto f1 = punto_parse_s(tt[5]);
	printf("8: %d,%ld,%f,%lf\n",a1,b1,c1,d1);
	printf("9: %s\n",int_pair_tostring(&e1,mem));
	printf("10: %s\n",punto_tostring(&f1,mem));
}

void test_types() {
	double a = 4;
	double b = 17;
	double * c = &b;
	double d = 18;
	copy(&a,&d,sizeof(double));
	printf("a = %lf,d = %lf\n",a,d);
	copy_in_pointer(&c,&d,sizeof(double));
	printf("d = %lf = b = %lf\n",d,b);
	int n = 0;
	char tt2[] = "34 389   23.5 -37.90 (3,-5) (34.1,-67.8)";
	char delimiters2[] = " ";
	char * tt[10];
	n = split_text(tt2, delimiters2,tt);
	printf("6: %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("7: %s\n", tt[i]);
	}
}


