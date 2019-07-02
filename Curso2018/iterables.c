/*
 * iterable.c
 *
 *  Created on: 1 jul. 2019
 *      Author: migueltoro
 */


#include "iterables.h"

iterable create_iterable(
		int size_state,
		bool (*has_next)(struct st * iterable, void * dependencies),
		void * (*next)(struct st * iterable, void * dependencies),
		void * (*see_next)(struct st * iterable, void * dependencies),
		void * dependencies,
		int sizeDependencies);

void * copy(int size, void * target, const void * source){
	memcpy(target,source,size);
	return target;
}

bool iterable_has_next(iterable * st) {
	return st->has_next(st,st->dependencies);
}

void * iterable_see_next(iterable * st){
	assert(iterable_has_next(st) && "no hay disponible un siguiente estado");
	return st->see_next(st,st->dependencies);
}

void * iterable_next(iterable * st) {
	assert(iterable_has_next(st) && "no hay disponible un siguiente estado");
	return st->next(st,st->dependencies);
}

iterable create_iterable(
		int size_state,
		bool (*has_next)(struct st * iterable, void * dependencies),
		void * (*next)(struct st * iterable, void * dependencies),
		void * (*see_next)(struct st * iterable, void * dependencies),
		void * dependencies,
		int sizeDependencies){
	memory_heap hp = memory_heap_create();
	void * state = memory_heap_get_memory(&hp,size_state);
	void * auxiliary_state = memory_heap_get_memory(&hp,size_state);
	void * dp = memory_heap_to_data(&hp,dependencies,sizeDependencies);
	iterable r = {hp,size_state,state,auxiliary_state,has_next,next,see_next,dp};
	return r;
}

typedef struct{
	iterable * depending_iterable;
	void * (*map_function)(void * target, void * source);
}dependencies_map;

bool iterable_map_has_next(iterable * current_iterable, void * dependencies){
	iterable * st = ((dependencies_map *) dependencies)->depending_iterable;
	return iterable_has_next(st);
}

void * iterable_map_see_next(iterable * current_iterable, void * dependencies){
	dependencies_map * d = (dependencies_map *) dependencies;
	iterable * st = d->depending_iterable;
    d->map_function(st->auxiliary_state,iterable_see_next(st));
    return st->auxiliary_state;
}

void * iterable_map_next(iterable * current_iterable, void * dependencies) {
	dependencies_map * d = (dependencies_map *) dependencies;
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

void next_depending_state(iterable * current_iterable, dependencies_filter * dependencies) {
	iterable * depending_iterable = dependencies->depending_iterable;
	while (iterable_has_next(depending_iterable)) {
		void * r = iterable_see_next(depending_iterable);
		if (dependencies->filter_predicate(r)) break;
		iterable_next(depending_iterable);
	}
	if(iterable_has_next(depending_iterable)){
		copy(current_iterable->size_state, current_iterable->state, iterable_see_next(depending_iterable));
	}
}

bool iterable_filter_has_next(iterable * current_iterable, void * dependencies) {
	dependencies_filter * d = (dependencies_filter *) dependencies;
	iterable * st = d->depending_iterable;
	return iterable_has_next(st);
}

void * iterable_filter_see_next(iterable * current_iterable, void * dependencies){
    return current_iterable->state;
}

void * iterable_filter_next(iterable * current_iterable, void * dependencies) {
	dependencies_filter * d = (dependencies_filter *) dependencies;
	iterable * depending_iterable = d->depending_iterable;
	copy(current_iterable->size_state,current_iterable->auxiliary_state,current_iterable->state);
	iterable_next(depending_iterable);
	next_depending_state(current_iterable,d);
	return current_iterable->auxiliary_state;
}


iterable iterable_filter(iterable * depending_iterable, int size_state, bool (*filter_predicate)(void *)) {
	dependencies_filter df = {depending_iterable,filter_predicate,true};
	int size_df = sizeof(dependencies_filter);
	iterable new_st = create_iterable(size_state,iterable_filter_has_next,iterable_filter_next,iterable_filter_see_next,&df,size_df);
	next_depending_state(&new_st,&df);
	return new_st;
}


typedef struct {
	long a;
	long b;
	long c;
}dependencies_range;

bool iterable_range_has_next(iterable * current_iterable, void * dependencies){
	dependencies_range * d = (dependencies_range *) dependencies;
	return *(long *)current_iterable->state < d->b;
}

void * iterable_range_see_next(iterable * current_iterable, void * dependencies){
    return current_iterable->state;
}

void * iterable_range_next(iterable * current_iterable, void * dependencies){
	dependencies_range * d = (dependencies_range *) dependencies;
	copy(sizeof(long),current_iterable->auxiliary_state, current_iterable->state);
	(*(long*) current_iterable->state) = (*(long*) current_iterable->state) +d->c;
	return current_iterable->auxiliary_state;
}

iterable iterable_range_long(long a, long b, long c){
	dependencies_range dr = {a,b,c};
	int size_dr = sizeof(dependencies_range);
	iterable new_st = create_iterable(sizeof(long),iterable_range_has_next,iterable_range_next,iterable_range_see_next,&dr,size_dr);
	return new_st;
}

typedef struct{
	FILE * file;
	bool is_done;
	bool has_next;
}dependencies_file;

bool iterable_file_has_next(iterable * current_iterable, void * dependencies) {
	dependencies_file * dp = (dependencies_file *) dependencies;
	if (!(dp->is_done)) {
		char * r = fgets(current_iterable->state, Tam_String, dp->file);
		if (r == NULL) {
			dp->has_next = false;
		} else {
			dp->has_next = true;
			remove_eol(current_iterable->state);
		}
		dp->is_done = true;
	}
	return dp->has_next;
}

void * iterable_file_see_next(iterable * current_iterable, void * dependencies){
    return current_iterable->state;
}

void * iterable_file_next(iterable * current_iterable,void * dependencies){
	dependencies_file * dp = (dependencies_file *) dependencies;
	dp->is_done = false;
	return current_iterable->state;
}


iterable file_iterable(char * file) {
	FILE * st = fopen(file,"r");
	assert(st != NULL && "no se encuentra el fichero");
	dependencies_file df = {st,false,false};
	int size_df = sizeof(dependencies_file);
	iterable s_file = create_iterable(Tam_String,iterable_file_has_next,iterable_file_next,iterable_file_see_next,&df,size_df);
	return s_file;
}

void iterable_free(iterable * st) {
	free(st->state);
	free(st->auxiliary_state);
	free(st->dependencies);
	memory_heap_free(&(st->hp));
}

list iterable_to_list(iterable * st, int size_element){
	list r = list_empty();
	while(iterable_has_next(st)){
		char * s = iterable_next(st);
		list_add(&r,s,size_element);
	}
	return r;
}

set iterable_to_set(iterable * st,
		int size_element,
		int (*equals)(const void *, const void *),
		char * (*tostring)(const void * e, char * mem)) {
	set r = set_empty(equals, tostring);
	while (iterable_has_next(st)) {
		char * s = iterable_next(st);
		set_add(&r, s, size_element);
	}
	return r;
}

hash_table counting(iterable * st,
		void * (*f_key)(void * e),
		int (*equals_key)(const void *, const void *),
		char * (*tostring_key)(const void * e, char * mem)){
	hash_table ht = hash_table_empty(equals_key, tostring_key);
	return ht;
}

hash_table grouping(iterable * st,
		void * (*f_key)(void * e),
		int (*equals_key)(const void *, const void *),
		char * (*tostring_key)(const void * e, char * mem)){
	hash_table ht = hash_table_empty(equals_key, tostring_key);
	return ht;
}

void test_iterables() {
	iterable fit = file_iterable("prueba.txt");
	while(iterable_has_next(&fit)){
		char * s = iterable_next(&fit);
		printf("%s",s);
	}
}
