/*
 * stream.c
 *
 *  Created on: 9 ago. 2018
 *      Author: migueltoro
 */


#include "stream.h"

int stream_equals(const void * e1, const void * e2);

memory_heap stream_memory = {0,0,NULL};

memory_heap * get_stream_memory(){
	if(stream_memory.elements == NULL) {
		stream_memory = memory_heap_create();
	}
	return &stream_memory;
}

void * get_mem_sm(int size){
	return tam_memory(get_stream_memory(),size);
}

void * get_int_sm(int a){
	return int_pointer_from_value(a,get_stream_memory());
}

void * get_long_sm(long a){
	return long_pointer_from_value(a,get_stream_memory());
}

void * get_value_sm(int size, void * value){
	return value_memory(get_stream_memory(),size, value);
}

void stream_memory_clear(){
	memory_heap_free(&stream_memory);
}


type stream_type = {sizeof(stream),NULL,stream_equals,NULL,NULL,NULL,NULL,"stream_type"};

int stream_has_next(stream st);
void * stream_next(stream st);

int stream_equals(const void * e1, const void * e2) {
	stream tt1 = *(stream *)e1;
	stream tt2 = *(stream *)e2;
	return  type_equals(tt1.state_type,tt2.state_type);
}

stream stream_create(type element_type, void * initial, bool (*has_next)(void *, void *),
		void * (*next)(void *, void *), void * dependencies) {
	stream st = {element_type,initial,has_next,next,dependencies};
	return st;
}

int stream_has_next(stream st) {
	return st.has_next(st.state,st.dependencies);
}

void * stream_next(stream st) {
	return st.next(st.state,st.dependencies);
}

void stream_to_buffer(string_buffer * buffer, stream st) {
	char nm[256];
	while(stream_has_next(st)){
		void * r = stream_next(st);
		string_buffer_add(buffer,st.state_type.tostring(nm,r));
	}
	string_buffer_close(buffer);
}

typedef struct{
	stream depending_stream;
	void * (*map_function)(void * target, void * source);
}dependencies_map_context;

bool stream_map_has_next(void * state, void * dependencies){
	stream st = ((dependencies_map_context *) dependencies)->depending_stream;
	return stream_has_next(st);
}

void * stream_map_next(void * state, void * dependencies) {
	dependencies_map_context * d = (dependencies_map_context *) dependencies;
	stream st = d->depending_stream;
	void * r = stream_next(st);
	void  * s = d->map_function(state,r);
	return s;
}


stream stream_map(stream st, type type_map, void * (*map_function)(void *, void*)) {
	dependencies_map_context dp = {st, map_function };
	int size = sizeof(dependencies_map_context);
	stream new_st = {type_map,
			get_mem_sm(type_map.size),
			stream_map_has_next,
			stream_map_next,
			get_value_sm(size, &dp)
	};
	return new_st;
}

typedef struct {
	stream depending_stream;
	bool (*filter_predicate)(void * source);
	bool has_next;
	bool done;
} dependencies_filter_context;

bool stream_filter_has_next(void * state, void * dependencies) {
	dependencies_filter_context * d = (dependencies_filter_context *) dependencies;
	stream st = d->depending_stream;
	void * r;
	if (!d->done) {
		d->has_next = 0;
		while(stream_has_next(st)) {
			r = stream_next(st);
			if(d->filter_predicate(r)){
				memcpy(state,r,st.state_type.size);
				d->has_next = 1;
				break;
			}
		}
		d->done = 1;
	}
	return d->has_next;
}

void * stream_filter_next(void * state, void * dependencies) {
	dependencies_filter_context * d = (dependencies_filter_context *) dependencies;
	d->done = false;
	return state;
}


stream stream_filter(stream st, bool (*filter_predicate)(void *)) {
	dependencies_filter_context dp = {st,filter_predicate,0,0};
	stream new_st = {st.state_type, get_mem_sm(st.state_type.size),
			stream_filter_has_next, stream_filter_next,
			get_value_sm(sizeof(dependencies_filter_context), &dp)};
	return new_st;
}

typedef struct {
	void * initial_value;
	bool (*hash_next)(void * element);
	void * (*next)(void * state);
}dependencies_iterate;

bool iterate_stream_has_next(void * state,void * dependencies){
	dependencies_iterate * d = (dependencies_iterate *) dependencies;
	return d->hash_next(state);
}

void * iterate_stream_next(void * state,void * dependencies){
	dependencies_iterate * d = (dependencies_iterate *) dependencies;
	return d->next(state);
}

stream stream_iterate(type element_type, void * initial_value, bool (*has_next)(void * element), void * (*next)(void * state)){
	dependencies_iterate dp = {initial_value,has_next,next};
		stream new_st = {element_type, get_value_sm(sizeof(element_type.size),dp.initial_value),
				iterate_stream_has_next, iterate_stream_next,
				get_value_sm(sizeof(dependencies_iterate), &dp)};
	return new_st;
}

typedef struct {
	int initial_value;
	bool (*hash_next)(int);
	int (*next)(int);
}dependencies_iterate_int;

bool iterate_stream_has_next_int(void * state,void * dependencies){
	dependencies_iterate_int * d = (dependencies_iterate_int *) dependencies;
	return d->hash_next(*(int*)state);
}

void * iterate_stream_next_int(void * state,void * dependencies){
	dependencies_iterate_int * d = (dependencies_iterate_int*) dependencies;
	int * next = (int *) state;
	* next = d->next(*(int*)state);
	return next;
}

stream stream_iterate_int(int initial_value, bool (*has_next)(int),int (*next)(int)){
	dependencies_iterate_int dp = {initial_value,has_next,next};
			stream new_st = {int_type, get_value_sm(sizeof(int_type.size),&dp.initial_value),
					iterate_stream_has_next_int, iterate_stream_next_int,
					get_value_sm(sizeof(dependencies_iterate_int), &dp)};
		return new_st;
}

typedef struct {
	double initial_value;
	bool (*hash_next)(double);
	double (*next)(double);
}dependencies_iterate_double;

bool iterate_stream_has_next_double(void * state,void * dependencies){
	dependencies_iterate_double * d = (dependencies_iterate_double *) dependencies;
	return d->hash_next(*(double*)state);
}

void * iterate_stream_next_double(void * state,void * dependencies){
	dependencies_iterate_double * d = (dependencies_iterate_double*) dependencies;
	double * next = (double *) state;
	* next = d->next(*(double*)state);
	return next;
}

stream stream_iterate_double(double initial_value, bool (*has_next)(double),double (*next)(double)){
	dependencies_iterate_double dp = {initial_value,has_next,next};
			stream new_st = {double_type, get_value_sm(sizeof(double_type.size),&dp.initial_value),
					iterate_stream_has_next_double, iterate_stream_next_double,
					get_value_sm(sizeof(dependencies_iterate_double), &dp)};
		return new_st;
}


typedef struct {
	tuple2_int initial_value;
	bool (*hash_next)(tuple2_int);
	tuple2_int (*next)(tuple2_int);
}dependencies_iterate_tuple2_int;

bool iterate_stream_has_next_tuple2_int(void * state,void * dependencies){
	dependencies_iterate_tuple2_int * d = (dependencies_iterate_tuple2_int *) dependencies;
	return d->hash_next(*(tuple2_int*)state);
}

void * iterate_stream_next_tuple2_int(void * state,void * dependencies){
	dependencies_iterate_tuple2_int * d = (dependencies_iterate_tuple2_int*) dependencies;
	tuple2_int * next = (tuple2_int *) state;
	* next = d->next(*(tuple2_int*)state);
	return next;
}

stream stream_iterate_tuple2_int(tuple2_int initial_value, bool (*has_next)(tuple2_int),tuple2_int (*next)(tuple2_int)){
	dependencies_iterate_tuple2_int dp = {initial_value,has_next,next};
			stream new_st = {tuple2_int_type, get_value_sm(sizeof(tuple2_int_type.size),&dp.initial_value),
					iterate_stream_has_next_tuple2_int, iterate_stream_next_tuple2_int,
					get_value_sm(sizeof(dependencies_iterate_double), &dp)};
		return new_st;
}


typedef struct {
	int a;
	int b;
	int c;
	int * old_state;
}dependencies_range;

bool range_stream_has_next(void * state,void * dependencies){
	dependencies_range * d = (dependencies_range *) dependencies;
	return *(int *)state < d->b;
}

void * range_stream_next(void * state,void * dependencies){
	dependencies_range * d = (dependencies_range *) dependencies;
	*d->old_state = *(int *)state;
	*(int *)state = *(int *)state +d->c;
	return d->old_state;
}

stream stream_range_int(int a, int b, int c){
	dependencies_range dp = {a,b,c,get_mem_sm(sizeof(int))};
	stream new_st = {int_type, get_int_sm(a),
			range_stream_has_next, range_stream_next,
			get_value_sm(sizeof(dependencies_range), &dp)};
	return new_st;
}

typedef struct{
	FILE * file;
	bool is_done;
	bool has_next;
}dependencies_file;

bool file_stream_has_next(void * state,void * dependencies){
	dependencies_file * dp = (dependencies_file *) dependencies;
	if(!(dp->is_done)){
		char * mem = (char *)state;
		char * r = fgets(mem,Tam_String, dp->file);
		if(r==NULL) {
			dp->has_next = 0;
		} else {
			remove_eol(r);
		}
		dp->is_done = 1;
	}
	return dp->has_next;
}

void * file_stream_next(void * state,void * dependencies){
	dependencies_file * dp = (dependencies_file *) dependencies;
	dp->is_done = 0;
	return state;
}


stream file_stream(char * file) {
	FILE * st = fopen(file,"r");
	assert(st != NULL);
	dependencies_file dp = {st,0,1};
	stream s_file = {string_type,
			tam_memory(get_stream_memory(),Tam_String),
			file_stream_has_next, file_stream_next,
			get_value_sm(sizeof(dependencies_file), &dp)};
	return s_file;
}

void stream_free(stream * st) {
	free(st->state);
}
