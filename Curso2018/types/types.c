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



// int type

int int_parse(char * text){
	int p;
	sscanf(text,"%d",&p);
	return p;
}

void * int_parse_g(void * out, char * text){
	int p;
	sscanf(text,"%d",&p);
	*(int *)out = p;
	return out;
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

bool int_equals(const void * e1, const void * e2){
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

int to_int(void * in){
	return *(int *) in;
}

int * to_int_pointer(void * in){
	return (int *) in;
}

void * int_copy(void * out, void * in){
	*(int *) out = *(int *) in;
	return out;
}

void * int_pointer_copy(void * out, void * in){
	*(int **) out = (int *) in;
	return out;
}

type int_type = {int_equals,int_tostring,int_naturalorder,int_copy,int_pointer_copy,int_parse_g,sizeof(int)};

// long type

long long_parse(char * text){
	long p;
	sscanf(text,"%ld",&p);
	return p;
}

void * long_parse_g(void * out, char * text){
	long p;
	sscanf(text,"%ld",&p);
	*(long *)out = p;
	return out;
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

bool long_equals(const void * e1,const  void * e2){
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

long to_long(void * in){
	return *(long *) in;
}

long * to_long_pointer(void * in){
	return (long *) in;
}

void * long_copy(void * out, void * in){
	*(long *) out = *(long *) in;
	return out;
}

void * long_pointer_copy(void * out, void * in){
	*(long **) out = (long *) in;
	return out;
}

type long_type = {long_equals,long_tostring,long_naturalorder,long_copy,long_pointer_copy,long_parse_g,sizeof(long)};

// float type

float float_parse(char * text){
	float p;
	sscanf(text,"%f",&p);
	return p;
}

void * float_parse_g(void * out, char * text){
	float p;
	sscanf(text,"%f",&p);
	*(float *)out = p;
	return out;
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

bool float_equals(const void * e1, const void * e2){
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

float to_float(void * in){
	return *(float *) in;
}

float * to_float_pointer(void * in){
	return (float *) in;
}

void * float_copy(void * out, void * in){
	*(float *) out = *(float *) in;
	return out;
}

void * float_pointer_copy(void * out, void * in){
	*(float **) out = (float *) in;
	return out;
}

type float_type = {float_equals,float_tostring,float_naturalorder,float_copy,float_pointer_copy,float_parse_g,sizeof(float)};

//double type

double double_parse(char * text){
	double p;
	sscanf(text,"%lf",&p);
	return p;
}

void * double_parse_g(void * out, char * text){
	double p;
	sscanf(text,"%lf",&p);
	*(double *)out = p;
	return out;
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

bool double_equals(const void * e1, const void * e2){
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

double to_double(void * in){
	return *(double *) in;
}

double * to_double_pointer(void * in){
	return (double *) in;
}

void * double_copy(void * out, void * in){
	*(double *) out = *(double *) in;
	return out;
}

void * double_pointer_copy(void * out, void * in){
	*(double **) out = (double *) in;
	return out;
}

type double_type = {double_equals,double_tostring,double_naturalorder,double_copy,double_pointer_copy,double_parse_g,sizeof(double)};

// int_pair

int_pair int_pair_parse(char * text){
	int_pair p;
	sscanf(text,"(%d,%d)",&p.a,&p.b);
	return p;
}

void * int_pair_parse_g(void * out, char * text){
	int_pair p;
	sscanf(text,"(%d,%d)",&p.a,&p.b);
	*(int_pair *)out = p;
	return out;
}

char * int_pair_tostring(const void * p, char * mem){
	int_pair np = *(int_pair *)p;
	sprintf(mem,"(%d,%d)",np.a,np.b);
	return mem;
}

bool int_pair_equals(const void * p1, const void * p2){
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

int_pair to_int_pair(void * in){
	return *(int_pair *) in;
}

int_pair * to_int_pair_pointer(void * in){
	return (int_pair *) in;
}

void * int_pair_copy(void * out, void * in){
	*(int_pair *) out = *(int_pair *) in;
	return out;
}

void * int_pair_pointer_copy(void * out, void * in){
	*(int_pair **) out = (int_pair *) in;
	return out;
}

type int_pair_type = {int_pair_equals,int_pair_tostring,int_pair_naturalorder,int_pair_copy,int_pair_pointer_copy,int_pair_parse_g,sizeof(int_pair)};

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

void * punto_parse_g(void * out, char * text){
	punto pt;
	sscanf(text,"(%lf,%lf)",&pt.x,&pt.y);
	*(punto *)out = pt;
	return out;
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

bool punto_equals(const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	return np1.x == np2.x && np1.y == np2.y;
}

int punto_naturalorder(const void * p1, const void * p2){
	punto np1 = *(punto *)p1;
	punto np2 = *(punto *)p2;
	double d1 = punto_distancia_al_origen(np1);
	double d2 = punto_distancia_al_origen(np2);
	return double_naturalorder(&d1,&d2);
}

punto to_punto(void * in){
	return *(punto *) in;
}

punto * to_punto_pointer(void * in) {
	return (punto *) in;
}

void * punto_copy(void * out, void * in){
	*(punto *) out = *(punto *) in;
	return out;
}

void * punto_pointer_copy(void * out, void * in){
	*(punto **) out = (punto *) in;
	return out;
}

type punto_type = {punto_equals,punto_tostring,punto_naturalorder,punto_copy,punto_pointer_copy,punto_parse_g,sizeof(punto)};

// pair type

void * pair_parse_g(void * out, char * text){
	pair_t * p = (pair_t *) out;
	char k[Tam_String];
	char v[Tam_String];
	sscanf(text,"(%s,%s)",k,v);
	p->key_type->parse(p->key,k);
	p->value_type->parse(p->value,v);
	return out;
}

char * pair_tostring(const void * e, char * mem){
	pair_t np = *(pair_t *)e;
	char m[Tam_String];
	char * key = np.key_type->tostring(np.key,m);
	char * value = np.value_type->tostring(np.value,m);
	sprintf(mem,"(%s,%s)",key,value);
	return mem;
}

bool pair_equals(const void * e1, const void * e2){
	pair_t * np1 = (pair_t *)e1;
	pair_t * np2 = (pair_t *)e2;
	return np1->key_type->equals(np1->key,np2->key) &&
		   np1->key_type->equals(np1->value,np2->value);
}

int pair_naturalorder(const void * e1, const void * e2){
	pair_t * np1 = (pair_t *)e1;
	pair_t * np2 = (pair_t *)e2;
	int r = np1->key_type->order(np1->key,np2->key);
	if(r==0) r = np1->key_type->order(np1->value,np2->value);
	return r;
}

pair_t to_pair(void * in){
	return *(pair_t *) in;
}
pair_t * to_pair_pointer(void * in){
	return (pair_t *) in;
}

void * pair_copy(void * out, void * in){
	*(pair_t *) out = *(pair_t *) in;
	return out;
}

void * pair_pointer_copy(void * out, void * in){
	*(pair_t **) out = (pair_t *) in;
	return out;
}

pair_t pair_of(pair p, type * t1, type * t2){
	pair_t r = {p.key,p.value,t1,t2};
	return r;
}

pair_t pair_of_2(void * key, void * value, type * t1, type * t2){
	pair_t r = {key,value,t1,t2};
	return r;
}

type pair_type = {pair_equals,pair_tostring,pair_naturalorder,pair_copy,pair_pointer_copy,pair_parse_g,sizeof(pair_t)};

// string type

void * string_parse_g(void * out, char * text){
	strcpy(out,text);
	return text;
}

char * string_tostring(const void * e, char * mem) {
	char * a = (char *) e;
	return a;
}

long string_hashcode(const void * e) {
	char * a = (char *) e;
	return hash(a);
}

bool string_equals(const void * e1, const void * e2) {
	char * a1 = (char *) e1;
	char * a2 = (char *) e2;
	return strcmp(a1, a2) == 0;
}

int string_naturalorder(const void * e1, const void * e2) {
	char * a1 = (char *) e1;
	char * a2 = (char *) e2;
	return strcmp(a1, a2);
}

char * to_string(void * in){
	return (char *) in;
}

void * string_copy(void * out, void * in){
	char * a = (char *) in;
	char * b = (char *) out;
	strcpy(b,a);
	return out;
}

void * string_pointer_copy(void * out, void * in){
	*(char **) out = (char *) in;
	return out;
}

type string_type = {string_equals,string_tostring,string_naturalorder,string_copy,string_pointer_copy,string_parse_g,Tam_String};


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
		tokens[i] = token;
		token = strtok(NULL,delimiters);
		i++;
	}
	*ntokens = i;
	return tokens;
}

// optional type

void * optional_parse_g(void * out, char * text){
	optional * r = (optional *) out;
	r->type->parse(r->value,text);
	return out;
}
char * optional_tostring(const void * e, char * mem){
	optional * r = (optional *) e;
	if(r->value == NULL){
		strcpy(mem,"null");
	} else {
		r->type->tostring(r->value,mem);
	}
	return mem;
}
bool optional_equals(const void * e1, const void * e2){
	optional * r1 = (optional *) e1;
	optional * r2 = (optional *) e2;
	return r1->type->equals(r1->value,r2->value);
}
int optional_naturalorder(const void * e1, const void * e2){
	optional * r1 = (optional *) e1;
	optional * r2 = (optional *) e2;
	return r1->type->order(r1->value,r2->value);
}
optional to_optional(void * in){
	optional r = *(optional *) in;
	return r;
}
optional * to_optional_pointer(void * in){
	optional * r = (optional *) in;
	return r;
}
void * optional_copy(void * out, void * in){
	optional * r1 = (optional *) in;
	optional * r2 = (optional *) out;
	r1->type->copy(r2->value,r1->value);
	return out;
}
void * optional_pointer_copy(void * out, void * in){
	optional * r1 = (optional *) in;
	optional * r2 = (optional *) out;
	r1->type->pointer_copy(r2->value,r1->value);
	return out;
}
optional optional_of(void * in, type * type){
	optional r = {in,type};
	return r;
}

type optional_type = {optional_equals,optional_tostring,optional_naturalorder,optional_copy,optional_pointer_copy,optional_parse_g,sizeof(optional)};

// void * type

void * void_star_pointer_copy(void * out, void * in){
	*(void **) out = in;
	return out;
}

type void_star_type = {NULL,NULL,NULL,NULL,void_star_pointer_copy,NULL,sizeof(void *)};

type none_type = {NULL,NULL,NULL,NULL,NULL,NULL,0};

// utilities

void * copy(void * out, void * in, int size){
	if(in != NULL) memcpy(out,in,size);
	else out = NULL;
	return out;
}

void * swap(void * out, void * in, int size){
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

void test_types(){
	double a = 4;
	double b = 7;
	double * c;
	double d = 18;
	void * h;
	double_type.copy(&a,&d);
	printf("%lf,%lf\n",a,d);
	double_type.pointer_copy(&c,&b);
	printf("%lf\n",to_double(c));
	void_star_type.pointer_copy(&h,&d);
	printf("%lf",to_double(h));
}

