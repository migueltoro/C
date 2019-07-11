/*
 * iterable.c
 *
 *  Created on: 1 jul. 2019
 *      Author: migueltoro
 */

#include "../types/iterables.h"

iterable create_iterable(
		int size_state,
		bool (*has_next)(struct st * iterable),
		void * (*next)(struct st * iterable),
		void * (*see_next)(struct st * iterable),
		void * dependencies,
		int size_dependencies);

void copy_state_to_auxiliary(iterable * st){
	memcpy(st->auxiliary_state,st->state,st->size_state);
}

bool iterable_has_next(iterable * st) {
	return st->has_next(st);
}

void * iterable_see_next(iterable * st){
	check_argument(iterable_has_next(st),__FILE__,__LINE__,"no hay disponible un siguiente estado");
	return st->see_next(st);
}

void * iterable_next(iterable * st) {
	check_argument(iterable_has_next(st),__FILE__,__LINE__,"no hay disponible un siguiente estado");
	return st->next(st);
}

iterable create_iterable(
		int size_state,
		bool (*has_next)(struct st * iterable),
		void * (*next)(struct st * iterable),
		void * (*see_next)(struct st * iterable),
		void * dependencies,
		int size_dependencies){
	memory_heap hp = memory_heap_create();
	void * state = memory_heap_get_memory(&hp,size_state);
	void * auxiliary_state = memory_heap_get_memory(&hp,size_state);
	void * dp = memory_heap_to_data(&hp,dependencies,size_dependencies);
	iterable r = {hp,size_state,state,auxiliary_state,has_next,next,see_next,dp};
	return r;
}

typedef struct{
	iterable * depending_iterable;
	void * (*map_function)(void * target, void * source);
}dependencies_map;

bool iterable_map_has_next(iterable * current_iterable){
	iterable * st = ((dependencies_map *) current_iterable->dependencies)->depending_iterable;
	return iterable_has_next(st);
}

void * iterable_map_see_next(iterable * current_iterable){
	dependencies_map * d = (dependencies_map *) current_iterable->dependencies;
	iterable * st = d->depending_iterable;
    d->map_function(st->auxiliary_state,iterable_see_next(st));
    return st->auxiliary_state;
}

void * iterable_map_next(iterable * current_iterable) {
	dependencies_map * d = (dependencies_map *) current_iterable->dependencies;
	iterable * depending_iterable = d->depending_iterable;
	void * r = iterable_next(depending_iterable);
	d->map_function(current_iterable->state, r);
	return current_iterable->state;
}


iterable iterable_map(iterable * depending_iterable, int size_state, void * (*map_function)(void * out, void * in)) {
	dependencies_map dp = {depending_iterable, map_function};
	int size_dp = sizeof(dependencies_map);
	iterable r = create_iterable(size_state,iterable_map_has_next,iterable_map_next,iterable_map_see_next,&dp,size_dp);
	return r;
}

typedef struct {
	iterable * depending_iterable;
	bool (*filter_predicate)(void * source);
	bool has_next;
} dependencies_filter;

void next_depending_state(iterable * current_iterable) {
	dependencies_filter * dependencies = (dependencies_filter *) current_iterable->dependencies;
	iterable * depending_iterable = dependencies->depending_iterable;
	while (iterable_has_next(depending_iterable)) {
		void * r = iterable_see_next(depending_iterable);
		if (dependencies->filter_predicate(r)) break;
		iterable_next(depending_iterable);
	}
	if(iterable_has_next(depending_iterable)){
		copy(current_iterable->state, iterable_see_next(depending_iterable),current_iterable->size_state);
	}
}

bool iterable_filter_has_next(iterable * current_iterable) {
	dependencies_filter * d = (dependencies_filter *) current_iterable->dependencies;
	iterable * st = d->depending_iterable;
	return iterable_has_next(st);
}

void * iterable_filter_see_next(iterable * current_iterable){
    return current_iterable->state;
}

void * iterable_filter_next(iterable * current_iterable) {
	dependencies_filter * d = (dependencies_filter *) current_iterable->dependencies;
	iterable * depending_iterable = d->depending_iterable;
	copy_state_to_auxiliary(current_iterable);
	iterable_next(depending_iterable);
	next_depending_state(current_iterable);
	return current_iterable->auxiliary_state;
}


iterable iterable_filter(iterable * depending_iterable, int size_state, bool (*filter_predicate)(void *)) {
	dependencies_filter df = {depending_iterable,filter_predicate,true};
	int size_df = sizeof(dependencies_filter);
	iterable new_st = create_iterable(size_state,iterable_filter_has_next,iterable_filter_next,iterable_filter_see_next,&df,size_df);
	next_depending_state(&new_st);
	return new_st;
}

///

typedef struct {
	long a;
	long b;
	long c;
}dependencies_range_long;

bool iterable_range_long_has_next(iterable * current_iterable){
	dependencies_range_long * d = (dependencies_range_long *) current_iterable->dependencies;
	return *(long *)current_iterable->state < d->b;
}

void * iterable_range_long_see_next(iterable * current_iterable){
    return current_iterable->state;
}

void * iterable_range_long_next(iterable * current_iterable){
	dependencies_range_long * d = (dependencies_range_long *) current_iterable->dependencies;
	copy_state_to_auxiliary(current_iterable);
	*((long*) current_iterable->state) = *((long*) current_iterable->state) +d->c;
	return current_iterable->auxiliary_state;
}

iterable iterable_range_long(long a, long b, long c){
	dependencies_range_long dr = {a,b,c};
	int size_dr = sizeof(dependencies_range_long);
	iterable new_st = create_iterable(sizeof(double),iterable_range_long_has_next,iterable_range_long_next,iterable_range_long_see_next,&dr,size_dr);
	*((long*) new_st.state) = a;
	return new_st;
}

typedef struct {
	double a;
	double b;
	double c;
}dependencies_range_double;

bool iterable_range_double_has_next(iterable * current_iterable){
	dependencies_range_double * d = (dependencies_range_double *) current_iterable->dependencies;
	return *(double *)current_iterable->state < d->b;
}

void * iterable_range_double_see_next(iterable * current_iterable){
    return current_iterable->state;
}

void * iterable_range_double_next(iterable * current_iterable){
	dependencies_range_double * d = (dependencies_range_double *) current_iterable->dependencies;
	copy_state_to_auxiliary(current_iterable);
	*((double*) current_iterable->state) = *((double*) current_iterable->state) +d->c;
	return current_iterable->auxiliary_state;
}

iterable iterable_range_double(double a, double b, double c){
	dependencies_range_double dr = {a,b,c};
	int size_dr = sizeof(dependencies_range_double);
	iterable new_st = create_iterable(sizeof(double),iterable_range_double_has_next,iterable_range_double_next,iterable_range_double_see_next,&dr,size_dr);
	*((double*) new_st.state) = a;
	return new_st;
}


typedef struct {
	void * initial_value;
	bool (*hash_next)(void * element);
	void * (*has_next)(void * out, void * in);
}dependencies_iterate;

bool iterable_iterate_has_next(iterable * current_iterable){
	dependencies_iterate * d = (dependencies_iterate *) current_iterable->dependencies;
	return d->hash_next(current_iterable->state);
}

void * iterable_iterate_see_next(iterable * current_iterable){
    return current_iterable->state;
}

void * iterable_iterate_next(iterable * current_iterable){
	dependencies_iterate * d = (dependencies_iterate *) current_iterable->dependencies;
	copy_state_to_auxiliary(current_iterable);
	d->has_next(current_iterable->state, current_iterable->state);
	return current_iterable->auxiliary_state;
}

iterable iterable_iterate(int size_state,
		void * initial_value,
		bool (*has_next)(void * element),
		void * (*next)(void * out, void * in)) {
	dependencies_iterate di = {initial_value, has_next, next};
	int size_di = sizeof(dependencies_iterate);
	iterable new_st = create_iterable(size_state,iterable_iterate_has_next,
			iterable_iterate_next,iterable_iterate_see_next,&di,size_di);
	copy(new_st.state,initial_value,size_state);
	return new_st;
}


typedef struct{
	char * text;
	char * token;
	char delimiters[Tam_String];
}dependencies_split;

bool iterable_split_has_next(iterable * current_iterable) {
	dependencies_split * dp = (dependencies_split *) current_iterable->dependencies;
	return dp->token != NULL;
}

void * iterable_split_see_next(iterable * current_iterable){
	dependencies_split * dp = (dependencies_split *) current_iterable->dependencies;
    return dp->token;
}

void * iterable_split_next(iterable * current_iterable){
	dependencies_split * dp = (dependencies_split *) current_iterable->dependencies;
	char * old = dp->token;
	dp->token = strtok(NULL,dp->delimiters);
	return old;
}

iterable split_iterable(char * text, const char * delimiters){
	int ln = strlen(text);
	dependencies_split ds;
	ds.text = malloc(ln+10);
	strcpy(ds.text,text);
	strcpy(ds.delimiters,delimiters);
	ds.token = strtok(ds.text,ds.delimiters);
	int size_ds = sizeof(dependencies_split);
	iterable s_list = create_iterable(sizeof(char *),iterable_split_has_next,iterable_split_next,iterable_split_see_next,&ds,size_ds);
	return s_list;
}


typedef struct{
	FILE * file;
	bool has_next;
}dependencies_file;

bool iterable_file_has_next(iterable * current_iterable) {
	dependencies_file * dp = (dependencies_file *) current_iterable->dependencies;
	return dp->has_next;
}

void * iterable_file_see_next(iterable * current_iterable){
    return current_iterable->state;
}

void * iterable_file_next(iterable * current_iterable){
	dependencies_file * dp = (dependencies_file *) current_iterable->dependencies;
	copy_state_to_auxiliary(current_iterable);
	char * r = fgets(current_iterable->state, Tam_String, dp->file);
	dp->has_next = r!=NULL;
	return current_iterable->auxiliary_state;
}


iterable file_iterable(char * file) {
	FILE * st = fopen(file,"r");
	check_not_null(st,__FILE__,__LINE__,"no se encuentra el fichero ");
	dependencies_file df = {st,false};
	int size_df = sizeof(dependencies_file);
	iterable s_file = create_iterable(Tam_String,iterable_file_has_next,iterable_file_next,iterable_file_see_next,&df,size_df);
	char * r = fgets(s_file.state,Tam_String,((dependencies_file *)s_file.dependencies)->file);
	((dependencies_file *)s_file.dependencies)->has_next = r!=NULL;
	return s_file;
}

char * iterable_tostring(iterable * st,
		char * (*tostring)(const void * e, char * mem),
		char * mem){
	return iterable_tostring_sep(st,tostring,",","{","}",mem);
}

char * iterable_tostring_sep(iterable * st,
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

void iterable_toconsole(iterable * st, char * (*tostring)(const void * e, char * mem)){
	return iterable_toconsole_sep(st,tostring,",", "{", "}");
}

void iterable_toconsole_sep(iterable * st, char * (*tostring)(const void * e, char * mem),
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

void write_iterable_to_file(char * file, iterable * st, char * tostring(const void * source, char * mem)){
	char mem[256];
	FILE * f = fopen(file, "wt");
	while (iterable_has_next(st)) {
			fprintf(f, "%s\n", tostring(iterable_next(st), mem));
	}
	fclose(f);
}


void iterable_free(iterable * st) {
	free(st->state);
	free(st->auxiliary_state);
	free(st->dependencies);
	memory_heap_free(&(st->hp));
}

bool multiplo(void * in){
	long p = to_long(in);
	return p%7 == 0;
}

void * fm(void * out, void * in){
	char * s = to_string(in);
	punto p = punto_parse(s);
	*to_punto_pointer(out) = p;
	return out;
}

bool ft(void * in){
	punto p = to_punto(in);
	Cuadrante c = punto_cuadrante(p);
	return c == PRIMERO;
}

void test_iterables() {
	char mem[500];
	iterable r = iterable_range_long(0, 500, 2);
	iterable f = iterable_filter(&r, sizeof(long), multiplo);
	printf("\n");
	iterable_toconsole(&f, long_tostring);
	printf("\n_______________\n");
	char delimiters[] = " ,;.";
	char text[] = "El Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	iterable sp = split_iterable(text,delimiters);
	iterable_toconsole(&sp, string_tostring);
	printf("\n_______________\n");
	iterable fit = file_iterable("prueba.txt");
	iterable fmap = iterable_map(&fit,sizeof(punto),fm);
	iterable ff = iterable_filter(&fmap,sizeof(punto),ft);
	char * s = iterable_tostring(&ff,punto_tostring,mem);
	printf("%s",s);
}


