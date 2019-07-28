/*
 * iterable.c
 *
 *  Created on: 1 jul. 2019
 *      Author: migueltoro
 */

#include "../types/iterables.h"

iterator iterable_create(
		int size_state,
		bool (*has_next)(struct st * iterator),
		void * (*next)(struct st * iterator),
		void * (*see_next)(struct st * iterator),
		void (*free_dependencies)(void * in),
		void * dependencies,
		int size_dependencies);

void iterable_copy_state_to_auxiliary(iterator * st){
	memcpy(st->auxiliary_state,st->state,st->size_state);
}

bool iterable_has_next(iterator * st) {
	return st->has_next(st);
}

void * iterable_see_next(iterator * st){
	check_argument(iterable_has_next(st),__FILE__,__LINE__,"no hay disponible un siguiente estado");
	return st->see_next(st);
}

void * iterable_next(iterator * st) {
	check_argument(iterable_has_next(st),__FILE__,__LINE__,"no hay disponible un siguiente estado");
	return st->next(st);
}

iterator iterable_create(
		int size_state,
		bool (*has_next)(struct st * iterator),
		void * (*next)(struct st * iterator),
		void * (*see_next)(struct st * iterator),
		void (*free_dependencies)(void * in),
		void * dependencies,
		int size_dependencies){
	void * state = malloc(size_state);
	void * auxiliary_state = malloc(size_state);
	void * dp = copy_and_mem(dependencies,size_dependencies);
	iterator r = {size_state,size_dependencies,state,auxiliary_state,has_next,next,see_next,free_dependencies,dp};
	return r;
}

bool has_next_false(iterator * st){
	return false;
}


iterator iterable_empty(){
	iterator r = {0,0,NULL,NULL,has_next_false,NULL,NULL,NULL,NULL};
	return r;
}

typedef struct{
	iterator * depending_iterable;
	void * (*map_function)(void * target, const void * source);
}dependencies_map;

bool iterable_map_has_next(iterator * current_iterable){
	iterator * st = ((dependencies_map *) current_iterable->dependencies)->depending_iterable;
	return iterable_has_next(st);
}

void * iterable_map_see_next(iterator * current_iterable){
	dependencies_map * d = (dependencies_map *) current_iterable->dependencies;
	iterator * depending_iterable = d->depending_iterable;
	return d->map_function(depending_iterable->state,iterable_see_next(depending_iterable));
}

void * iterable_map_next(iterator * current_iterable) {
	dependencies_map * d = (dependencies_map *) current_iterable->dependencies;
	iterator * depending_iterable = d->depending_iterable;
	void * r = iterable_next(depending_iterable);
	return d->map_function(current_iterable->state, r);
}


iterator iterable_map(iterator * depending_iterable, int size_state, void * (*map_function)(void * out, const void * in)) {
	dependencies_map dp = {depending_iterable, map_function};
	int size_dp = sizeof(dependencies_map);
	iterator r = iterable_create(size_state,iterable_map_has_next,iterable_map_next,iterable_map_see_next,NULL,&dp,size_dp);
	return r;
}


typedef struct{
	iterator actual_iterable;
	iterator * depending_iterable;
	void * (*map_function)(void * target, void * source);
}dependencies_flatmap;

bool iterable_flatmap_has_next(iterator * current_iterable){
	dependencies_flatmap * d = (dependencies_flatmap *) current_iterable->dependencies;
	iterator act = d->actual_iterable;
	return iterable_has_next(&act);
}

void * iterable_flatmap_see_next(iterator * current_iterable){
	dependencies_flatmap * d = (dependencies_flatmap *) current_iterable->dependencies;
	iterator st = d->actual_iterable;
	return iterable_see_next(&st);
}

void * iterable_flatmap_next(iterator * current_iterable) {
	dependencies_flatmap * d = (dependencies_flatmap *) current_iterable->dependencies;
	iterator * depending_iterable = d->depending_iterable;
	copy(current_iterable->auxiliary_state,iterable_next(&d->actual_iterable),current_iterable->size_state);
	while(!iterable_has_next(&d->actual_iterable)){
		if(iterable_has_next(depending_iterable)){
			iterable_free(&d->actual_iterable);
			d->map_function(&d->actual_iterable,iterable_next(depending_iterable));
		}
		else break;
	}
	return current_iterable->auxiliary_state;
}


iterator iterable_flatmap(iterator * depending_iterable, int size_state,
		void * (*map_function)(void * out, void * in)) {
	iterator actual_iterable;
	dependencies_flatmap dp = {actual_iterable, depending_iterable, map_function};
	int size_dp = sizeof(dependencies_flatmap);
	do {
		if(iterable_has_next(depending_iterable))
			map_function(&dp.actual_iterable, iterable_next(depending_iterable));
		else break;
	} while (!iterable_has_next(&dp.actual_iterable) && iterable_has_next(depending_iterable));
	iterator r = iterable_create(size_state, iterable_flatmap_has_next,
			iterable_flatmap_next, iterable_flatmap_see_next, NULL, &dp, size_dp);
	return r;
}


typedef struct {
	iterator * depending_iterable;
	bool (*filter_predicate)(void * source);
	bool has_next;
} dependencies_filter;

void next_depending_state(iterator * current_iterable) {
	dependencies_filter * dependencies = (dependencies_filter *) current_iterable->dependencies;
	iterator * depending_iterable = dependencies->depending_iterable;
	while (iterable_has_next(depending_iterable)) {
		void * r = iterable_see_next(depending_iterable);
		if (dependencies->filter_predicate(r)) break;
		iterable_next(depending_iterable);
	}
	if(iterable_has_next(depending_iterable)){
		copy(current_iterable->state, iterable_see_next(depending_iterable),current_iterable->size_state);
	}
}

bool iterable_filter_has_next(iterator * current_iterable) {
	dependencies_filter * d = (dependencies_filter *) current_iterable->dependencies;
	iterator * st = d->depending_iterable;
	return iterable_has_next(st);
}

void * iterable_filter_see_next(iterator * current_iterable){
    return current_iterable->state;
}

void * iterable_filter_next(iterator * current_iterable) {
	dependencies_filter * d = (dependencies_filter *) current_iterable->dependencies;
	iterator * depending_iterable = d->depending_iterable;
	iterable_copy_state_to_auxiliary(current_iterable);
	iterable_next(depending_iterable);
	next_depending_state(current_iterable);
	return current_iterable->auxiliary_state;
}


iterator iterable_filter(iterator * depending_iterable, int size_state, bool (*filter_predicate)(void *)) {
	dependencies_filter df = {depending_iterable,filter_predicate,true};
	int size_df = sizeof(dependencies_filter);
	iterator new_st = iterable_create(size_state,iterable_filter_has_next,iterable_filter_next,iterable_filter_see_next,NULL,&df,size_df);
	next_depending_state(&new_st);
	return new_st;
}

void * _old_f_consecutive_pair;
void * _new_f_consecutive_pair;
int _size_f_consecutive_pair;

char * pair_long_long(pair * p, char * mem);

pair * _f_consecutive_pair(pair * out, void * in) {
	if(out!=NULL){
		copy(_old_f_consecutive_pair,_new_f_consecutive_pair,_size_f_consecutive_pair);
		pair p = {_old_f_consecutive_pair,in};
		*out = p;

	}
	copy(_new_f_consecutive_pair,in,_size_f_consecutive_pair);
	return out;
}

iterator iterable_consecutive_pairs(iterator * st,int size_element){
	_size_f_consecutive_pair = size_element;
	free(_old_f_consecutive_pair);
	free(_new_f_consecutive_pair);
	_old_f_consecutive_pair = malloc(size_element);
	_new_f_consecutive_pair = malloc(size_element);
	iterator r = iterable_empty();
	if(iterable_has_next(st)) {
		void * e = iterable_next(st);
		_f_consecutive_pair(NULL,e);
	}
	if(iterable_has_next(st)) {
		r = iterable_map(st,sizeof(pair),_f_consecutive_pair);
	}
	return r;
}

pair_enumerate * _f_pair_enumerate(pair_enumerate * out, void * in) {
	static int n;
	if (in == NULL) {
		n = 0;
		return out;
	}
	pair_enumerate p = {in, n };
	*out = p;
	n = n+1;
	return out;
}

iterator iterable_enumerate(iterator * st){
	_f_pair_enumerate(NULL,NULL);
	iterator r = iterable_map(st,sizeof(pair_enumerate),_f_pair_enumerate);
	return r;
}

typedef struct {
	long a;
	long b;
	long c;
}dependencies_range_long;

bool iterable_range_long_has_next(iterator * current_iterable){
	dependencies_range_long * d = (dependencies_range_long *) current_iterable->dependencies;
	return *(long *)current_iterable->state < d->b;
}

void * iterable_range_long_see_next(iterator * current_iterable){
    return current_iterable->state;
}

void * iterable_range_long_next(iterator * current_iterable){
	dependencies_range_long * d = (dependencies_range_long *) current_iterable->dependencies;
	iterable_copy_state_to_auxiliary(current_iterable);
	*((long*) current_iterable->state) = *((long*) current_iterable->state) +d->c;
	return current_iterable->auxiliary_state;
}

iterator iterable_range_long(long a, long b, long c){
	dependencies_range_long dr = {a,b,c};
	int size_dr = sizeof(dependencies_range_long);
	iterator new_st = iterable_create(sizeof(double),iterable_range_long_has_next,iterable_range_long_next,iterable_range_long_see_next,NULL,&dr,size_dr);
	*((long*) new_st.state) = a;
	return new_st;
}

typedef struct {
	double a;
	double b;
	double c;
}dependencies_range_double;

bool iterable_range_double_has_next(iterator * current_iterable){
	dependencies_range_double * d = (dependencies_range_double *) current_iterable->dependencies;
	return *(double *)current_iterable->state < d->b;
}

void * iterable_range_double_see_next(iterator * current_iterable){
    return current_iterable->state;
}

void * iterable_range_double_next(iterator * current_iterable){
	dependencies_range_double * d = (dependencies_range_double *) current_iterable->dependencies;
	iterable_copy_state_to_auxiliary(current_iterable);
	*((double*) current_iterable->state) = *((double*) current_iterable->state) +d->c;
	return current_iterable->auxiliary_state;
}

iterator iterable_range_double(double a, double b, double c){
	dependencies_range_double dr = {a,b,c};
	int size_dr = sizeof(dependencies_range_double);
	iterator new_st = iterable_create(sizeof(double),iterable_range_double_has_next,iterable_range_double_next,iterable_range_double_see_next,NULL,&dr,size_dr);
	*((double*) new_st.state) = a;
	return new_st;
}


typedef struct {
	void * initial_value;
	bool (*hash_next)(void * element);
	void * (*has_next)(void * out, void * in);
}dependencies_iterate;

bool iterable_iterate_has_next(iterator * current_iterable){
	dependencies_iterate * d = (dependencies_iterate *) current_iterable->dependencies;
	return d->hash_next(current_iterable->state);
}

void * iterable_iterate_see_next(iterator * current_iterable){
    return current_iterable->state;
}

void * iterable_iterate_next(iterator * current_iterable){
	dependencies_iterate * d = (dependencies_iterate *) current_iterable->dependencies;
	iterable_copy_state_to_auxiliary(current_iterable);
	d->has_next(current_iterable->state, current_iterable->state);
	return current_iterable->auxiliary_state;
}

iterator iterable_iterate(int size_state,
		void * initial_value,
		bool (*has_next)(void * element),
		void * (*next)(void * out, void * in)) {
	dependencies_iterate di = {initial_value, has_next, next};
	int size_di = sizeof(dependencies_iterate);
	iterator new_st = iterable_create(size_state,iterable_iterate_has_next,
			iterable_iterate_next,iterable_iterate_see_next,NULL,&di,size_di);
	copy(new_st.state,initial_value,size_state);
	return new_st;
}

typedef struct{
	char * text;
	int size_text;
	char * token;
	char * delimiters;
	int size_delimiters;
}dependencies_split;

bool iterable_split_has_next(iterator * current_iterable) {
	dependencies_split * dp = (dependencies_split *) current_iterable->dependencies;
	return dp->token != NULL;
}

void * iterable_split_see_next(iterator * current_iterable){
	dependencies_split * dp = (dependencies_split *) current_iterable->dependencies;
    return dp->token;
}

void * iterable_split_next(iterator * current_iterable){
	dependencies_split * dp = (dependencies_split *) current_iterable->dependencies;
	char * old = dp->token;
	dp->token = strtok(NULL,dp->delimiters);
	return old;
}

void create_dependencies_split(dependencies_split * ds){
	ds->text = malloc(ds->size_text);
	ds->delimiters = malloc(ds->size_delimiters);
}

void dependencies_split_free(dependencies_split * ds){
	free(ds->text);
	free(ds->delimiters);
	free(ds);
}


iterator split_iterable_pchar(char * text, const char * delimiters) {
	dependencies_split ds;
	ds.size_text = strlen(text)+2;
	ds.size_delimiters = strlen(delimiters)+2;
	create_dependencies_split(&ds);
	int size_ds = sizeof(dependencies_split);
	strcpy(ds.text,text);
	strcpy(ds.delimiters,delimiters);
	ds.token = strtok(ds.text,delimiters);
	iterator r = iterable_create(0, iterable_split_has_next,
			iterable_split_next, iterable_split_see_next,dependencies_split_free, &ds, size_ds);
	return r;
}


iterator * pchar_to_iterable_pchar(iterator * out, char * text){
	*out = split_iterable_pchar(text," ,;.()");
	return out;
}

typedef struct{
	FILE * file;
	bool has_next;
}dependencies_file;

void free_dependencies_file(dependencies_file * df){
	fclose(df->file);
}

bool iterable_file_has_next(iterator * current_iterable) {
	dependencies_file * dp = (dependencies_file *) current_iterable->dependencies;
	return dp->has_next;
}

void * iterable_file_see_next(iterator * current_iterable){
    return current_iterable->state;
}

void * iterable_file_next(iterator * current_iterable){
	dependencies_file * dp = (dependencies_file *) current_iterable->dependencies;
	iterable_copy_state_to_auxiliary(current_iterable);
	char * r = fgets(current_iterable->state, Tam_String, dp->file);
	dp->has_next = r!=NULL;
	remove_eol_s(current_iterable->auxiliary_state);
	return current_iterable->auxiliary_state;
}


iterator file_iterable_pchar(char * file) {
	FILE * st = fopen(file,"r");
	char  ms[Tam_String] = "no se encuentra el fichero ";
	check_not_null(st,__FILE__,__LINE__,strcat(ms,file));
	dependencies_file df = {st,false};
	int size_df = sizeof(dependencies_file);
	iterator s_file = iterable_create(Tam_String,iterable_file_has_next,iterable_file_next,
			iterable_file_see_next,free_dependencies_file,&df,size_df);
	char * r = fgets(s_file.state,Tam_String,((dependencies_file *)s_file.dependencies)->file);
	((dependencies_file *)s_file.dependencies)->has_next = r!=NULL;
	return s_file;
}

char * iterable_tostring(iterator * st,
		char * (*tostring)(const void * e, char * mem),
		char * mem){
	return iterable_tostring_sep(st,tostring,",","{","}",mem);
}

char * iterable_tostring_sep(iterator * st,
		char * (*tostring)(const void * e, char * mem),
		char * sep,
		char * prefix,
		char * suffix,
		char * mem){
	char m[Tam_String];
	bool first = true;
	strcpy(mem,prefix);
	while(iterable_has_next(st)){
		void *  next = iterable_next(st);
		char * ns = tostring(next,m);
		if(first){
			first = false;
			strcat(mem,ns);
		} else {
			strcat(mem,sep);
			strcat(mem,ns);
		}
	}
	strcat(mem,suffix);
	return mem;
}

void iterable_toconsole(iterator * st, char * (*tostring)(const void * e, char * mem)){
	iterable_toconsole_sep(st,tostring,",", "{", "}");
}

void iterable_toconsole_sep(iterator * st, char * (*tostring)(const void * e, char * mem),
		char * sep, char * prefix, char * suffix) {
	char m[Tam_String];
	bool first = true;
	printf("%s",prefix);
	while (iterable_has_next(st)) {
		void * next = iterable_next(st);
		char * ns = tostring(next, m);
		if (first) first = false;
		else printf("%s",sep);
		printf("%s",ns);
	}
	printf("%s",suffix);
}

void write_iterable_to_file(char * file, iterator * st, char * tostring(const void * source, char * mem)){
	char mem[256];
	FILE * f = fopen(file, "wt");
	while (iterable_has_next(st)) {
			fprintf(f, "%s\n", tostring(iterable_next(st), mem));
	}
	fclose(f);
}

void iterable_free(iterator * st) {
	free(st->state);
	free(st->auxiliary_state);
	if(st->free_dependencies != NULL) st->free_dependencies(st->dependencies);
	else free(st->dependencies);
}


bool multiplo(long * in){
	return (*in)%7 == 0;
}


bool ft(punto * in){
	Cuadrante c = punto_cuadrante(in);
	return c == PRIMERO;
}

long * cuadrado(long * out,long * in){
	*out = (*in)*(*in);
	return out;
}

char * pair_long_long(pair * p, char * mem){
	sprintf(mem,"(%ld,%ld)",*(long*) p->key, *(long*) p->value);
	return mem;
}

char * pair_enumerate_long(pair_enumerate * p, char * mem){
	sprintf(mem,"(%ld,%d)",*(long*) p->key, p->n);
	return mem;
}

char * pair_enumerate_pchar(pair_enumerate * p, char * mem){
	sprintf(mem,"(%s,%d)",(char*) p->key, p->n);
	return mem;
}

char * pair_pchar_pchar(pair * p, char * mem){
	sprintf(mem,"(%s,%s)",(char*) p->key, (char *) p->value);
	return mem;
}

void test_iterables() {
	char mem[500];
	iterator r = iterable_range_long(0, 500, 2);
	iterator f = iterable_filter(&r, sizeof(long), multiplo);
	iterator s = iterable_map(&f,sizeof(long),cuadrado);
	printf("\n");
	iterable_toconsole(&s, long_tostring);
	printf("\n_______________\n");
	char delimiters[] = " ,;.";
	char text[] = "El    Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	iterator sp = split_iterable_pchar(text,delimiters);
	iterable_toconsole(&sp, pchar_tostring);
	printf("\n_______________\n");
	iterator fit = file_iterable_pchar("ficheros/prueba.txt");
	iterator fmap = iterable_map(&fit,sizeof(punto),punto_parse);
	iterator ff = iterable_filter(&fmap,sizeof(punto),ft);
	char * rs = iterable_tostring(&ff,punto_tostring,mem);
	printf("\n%s\n",rs);
	r = iterable_range_long(0, 9, 2);
	iterator r2 = iterable_consecutive_pairs(&r,sizeof(long));
	iterable_toconsole(&r2,pair_long_long);
	printf("\n_______________\n");
	r = iterable_range_long(0, 9, 2);
	r2 = iterable_enumerate(&r);
	iterable_toconsole(&r2,pair_enumerate_long);
}

void test_iterables2() {
	char mem[500];
	iterator r = iterable_range_long(0, 14, 2);
	iterator r2 = r;
	iterator r3 = r2;
	printf("\n");
	iterable_toconsole(&r3, long_tostring);
	iterator fit = file_iterable_pchar("ficheros/prueba.txt");
	iterator fmap = iterable_map(&fit,sizeof(punto),punto_parse);
	iterator ff = iterable_filter(&fmap,sizeof(punto),ft);
	iterator rr = ff;
	char * rs = iterable_tostring(&ff,punto_tostring,mem);
	printf("\n%s\n",rs);
	iterator p1 = split_iterable_pchar("     En un lugar de la Mancha, de cuyo nombre no quiero"," ,;.");
	iterator p2 = p1;
	iterable_toconsole(&p1,pchar_tostring);
	printf("\n_________________\n");
	iterator p3;
	char text[] = "El    Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	pchar_to_iterable_pchar(&p3,text);
	iterable_toconsole(&p3, pchar_tostring);
	iterable_free(&p3);
	printf("\n_________________\n");
	char text2[] = "El    Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	pchar_to_iterable_pchar(&p3,text2);
	iterator it = iterable_consecutive_pairs(&p3,20);
	iterable_toconsole(&it,pair_pchar_pchar);
	printf("\n______________\n");
	char text3[] = "El    Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	pchar_to_iterable_pchar(&p3,text2);
	iterator it2 = iterable_enumerate(&p3);
	iterable_toconsole(&it2,pair_enumerate_pchar);
}

void test_iterables3(){
	iterator fit = file_iterable_pchar("ficheros/prueba2.txt");
	iterator fit2 = iterable_filter(&fit, Tam_String, pchar_not_all_space);
	iterator fit3 = iterable_map(&fit2,Tam_String, remove_eol);
	iterator fmap = iterable_flatmap(&fit3,Tam_String,pchar_to_iterable_pchar);
	iterable_toconsole_sep(&fmap,pchar_tostring,",","{","}");
	printf("\n_________________\n");
	iterator git1 = file_iterable_pchar("ficheros/quijote.txt");
	iterator git2 = iterable_filter(&git1,Tam_String, pchar_not_all_space);
	iterator git3 = iterable_map(&git2,Tam_String,remove_eol);
	iterator gmap = iterable_flatmap(&git3,Tam_String,pchar_to_iterable_pchar);
	int n =0;
	while(iterable_has_next(&gmap)){
		n++;
		char * s = (char *) iterable_next(&gmap);
		printf("%s\n",s);
	}
	printf("Número de palabras %d",n);
	iterable_free(&git1);
	iterable_free(&git2);
	iterable_free(&git3);
	iterable_free(&gmap);
	printf("\n_______________\n");
}


