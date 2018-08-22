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
	return memory_heap_tam_memory(get_stream_memory(),size);
}

void * get_int_sm(int a){
	return int_pointer_from_value(a,get_stream_memory());
}

void * get_long_sm(long a){
	return long_pointer_from_value(a,get_stream_memory());
}

void * get_value_sm(int size, void * value){
	return memory_heap_memory_for_value(get_stream_memory(),size, value);
}

void stream_memory_clear(){
	memory_heap_free(&stream_memory);
}

type stream_type = {1,NULL,sizeof(stream),NULL,stream_equals,NULL,NULL,NULL,NULL,"stream_type"};

int stream_has_next(stream * st);
void * stream_see_next(stream * st);
void * stream_next(stream * st);

int stream_equals(const void * e1, const void * e2) {
	stream tt1 = *(stream *)e1;
	stream tt2 = *(stream *)e2;
	return  type_equals(tt1.state_type,tt2.state_type);
}

stream stream_create(type state_type,void * initial_state, bool (*has_next)(stream *, void *),
		void * (*next)(stream *, void *), void * dependencies) {
	stream st = {
			state_type,
			get_mem_sm(state_type.size_type),
			get_mem_sm(state_type.size_type),
			has_next,
			next,
			dependencies};
	state_type.copy(st.state,initial_state);
	return st;
}

int stream_has_next(stream * st) {
	return st->has_next(st,st->dependencies);
}

void * stream_see_next(stream * st){
	assert(stream_has_next(st));
	return st->state;
}

void * stream_next(stream * st) {
	assert(stream_has_next(st));
	return st->next(st,st->dependencies);
}

void stream_to_buffer(string_buffer * buffer, stream * st) {
	char nm[256];
	string_buffer_add_prefix(buffer);
	while(stream_has_next(st)){
		void * r = stream_next(st);
		string_buffer_add(buffer,st->state_type.tostring(nm,r));
	}
	string_buffer_add_sufix(buffer);
	string_buffer_close(buffer);
}

typedef struct{
	stream * depending_stream;
	void * (*map_function)(void * target, void * source);
}dependencies_map;

bool stream_map_has_next(stream * current_stream, void * dependencies){
	stream * st = ((dependencies_map *) dependencies)->depending_stream;
	return stream_has_next(st);
}

void * stream_map_next(stream * current_stream, void * dependencies) {
	dependencies_map * d = (dependencies_map *) dependencies;
	stream * depending_stream = d->depending_stream;
	void * r = stream_next(depending_stream);
	assert(*(long*)r<30);
	d->map_function(current_stream->state, r);
	return current_stream->state;
}


stream stream_map(stream  * depending_stream, type type_map, void * (*map_function)(void * out, void * in)) {
	dependencies_map dp = {depending_stream, map_function };
	int size = sizeof(dependencies_map);
	stream sm = {
			type_map,
			get_mem_sm(type_map.size_type),
			get_mem_sm(type_map.size_type),
			stream_map_has_next,
			stream_map_next,
			get_value_sm(size, &dp)
	};
	return sm;
}

typedef struct {
	stream * depending_stream;
	bool (*filter_predicate)(void * source);
	bool has_next;
} dependencies_filter;

void next_depending_state(stream * current_stream, dependencies_filter * dependencies) {
	stream * depending_stream = dependencies->depending_stream;
	while (stream_has_next(depending_stream)) {
		void * r = stream_see_next(depending_stream);
		if (dependencies->filter_predicate(r)) break;
		stream_next(depending_stream);
	}
	if (!stream_has_next(depending_stream)) dependencies->has_next = false;
	current_stream->state_type.copy(current_stream->state, depending_stream->state);
}

bool stream_filter_has_next(stream * current_stream, void * dependencies) {
	dependencies_filter * d = (dependencies_filter *) dependencies;
	return d->has_next;
}

void * stream_filter_next(stream * current_stream, void * dependencies) {
	dependencies_filter * d = (dependencies_filter *) dependencies;
	current_stream->state_type.copy(current_stream->auxiliary_state,current_stream->state);
	stream_next(d->depending_stream);
	next_depending_state(current_stream,d);
	return current_stream->auxiliary_state;
}


stream stream_filter(stream * depending_stream, bool (*filter_predicate)(void *)) {
	dependencies_filter d = {depending_stream,filter_predicate,true};
	stream new_st = {
			depending_stream->state_type,
			get_value_sm(sizeof(depending_stream->state_type.size_type), stream_see_next(d.depending_stream)),
			get_mem_sm(depending_stream->state_type.size_type),
			stream_filter_has_next,
			stream_filter_next,
			get_value_sm(sizeof(dependencies_filter), &d)
	};
	next_depending_state(&new_st,&d);
	return new_st;
}

typedef struct {
	type element_type;
	void * initial_value;
	bool (*hash_next)(void * element);
	void * (*next)(void * state);
}dependencies_iterate;

bool iterate_stream_has_next(stream * current_stream,void * dependencies){
	dependencies_iterate * d = (dependencies_iterate *) dependencies;
	return d->hash_next(current_stream->state);
}

void * iterate_stream_next(stream * current_stream, void * dependencies){
	dependencies_iterate * d = (dependencies_iterate *) dependencies;
	d->element_type.copy(current_stream->auxiliary_state,current_stream->state);
	d->next(current_stream->state);
	return current_stream->auxiliary_state;
}

stream stream_iterate(type element_type, void * initial_value, bool (*has_next)(void * element), void * (*next)(void * state)) {
	dependencies_iterate dp = { element_type, initial_value, has_next, next };
	stream new_st = {
			element_type,
			get_value_sm(sizeof(element_type.size_type),
			dp.initial_value),
			get_mem_sm(sizeof(element_type.size_type)),
			iterate_stream_has_next,
			iterate_stream_next, get_value_sm(sizeof(dependencies_iterate), &dp)
	};
	return new_st;
}

typedef struct {
	long initial_value;
	bool (*hash_next)(long);
	long (*next)(long);
}dependencies_iterate_long;

bool iterate_stream_has_next_long(stream * current_stream,void * dependencies){
	dependencies_iterate_long * d = (dependencies_iterate_long *) dependencies;
	return d->hash_next(*(long*)current_stream->state);
}

void * iterate_stream_next_long(stream * current_stream,void * dependencies){
	dependencies_iterate_long * d = (dependencies_iterate_long*) dependencies;
	long_type.copy(current_stream->auxiliary_state,current_stream->state);
	*(long*)current_stream->state = d->next(*(long*)current_stream->state);
	return current_stream->auxiliary_state;
}

stream stream_iterate_long(long initial_value, bool (*has_next)(long),long (*next)(long)){
	dependencies_iterate_long dp = {initial_value,has_next,next};
	stream new_st = {
					long_type,
					get_value_sm(sizeof(long_type.size_type),&initial_value),
					get_mem_sm(sizeof(long_type.size_type)),
					iterate_stream_has_next_long,
					iterate_stream_next_long,
					get_value_sm(sizeof(dependencies_iterate_long), &dp)
	};
	return new_st;
}

typedef struct {
	double initial_value;
	bool (*hash_next)(double);
	double (*next)(double);
}dependencies_iterate_double;

bool iterate_stream_has_next_double(stream * current_stream,void * dependencies){
	dependencies_iterate_double * d = (dependencies_iterate_double *) dependencies;
	return d->hash_next(*(double*)current_stream->state);
}

void * iterate_stream_next_double(stream * current_stream, void * dependencies) {
	dependencies_iterate_double * d = (dependencies_iterate_double*) dependencies;
	double_type.copy(current_stream->auxiliary_state, current_stream->state);
	*(double*)current_stream->state = d->next(*(double*) current_stream->state);
	return current_stream->auxiliary_state;
}

stream stream_iterate_double(double initial_value, bool (*has_next)(double),double (*next)(double)){
	dependencies_iterate_double dp = {initial_value,has_next,next};
			stream new_st = {
					double_type,
					get_value_sm(sizeof(double_type.size_type),&dp.initial_value),
					get_mem_sm(sizeof(double_type.size_type)),
					iterate_stream_has_next_double,
					iterate_stream_next_double,
					get_value_sm(sizeof(dependencies_iterate_double), &dp)};
		return new_st;
}



typedef struct {
	long a;
	long b;
	long c;
}dependencies_range;

bool range_stream_has_next(stream * current_stream, void * dependencies){
	dependencies_range * d = (dependencies_range *) dependencies;
	return *(long *)current_stream->state < d->b;
}

void * range_stream_next(stream * current_stream, void * dependencies){
	dependencies_range * d = (dependencies_range *) dependencies;
	long_type.copy(current_stream->auxiliary_state, current_stream->state);
	(*(long*) current_stream->state) = (*(long*) current_stream->state) +d->c;
	return current_stream->auxiliary_state;
}

stream stream_range_int(long a, long b, long c){
	dependencies_range dp = {a,b,c};
	stream new_st = {
			int_type,
			get_int_sm(a),
			get_mem_sm(sizeof(long)),
			range_stream_has_next,
			range_stream_next,
			get_value_sm(sizeof(dependencies_range), &dp)};
	return new_st;
}

typedef struct{
	FILE * file;
	bool is_done;
	bool has_next;
}dependencies_file;

bool file_stream_has_next(stream * current_stream,void * dependencies){
	dependencies_file * dp = (dependencies_file *) dependencies;
	if(!(dp->is_done)){
		char * mem = (char *)current_stream->state;
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

void * file_stream_next(stream * current_stream,void * dependencies){
	dependencies_file * dp = (dependencies_file *) dependencies;
	dp->is_done = 0;
	return current_stream->state;
}


stream file_stream(char * file) {
	FILE * st = fopen(file,"r");
	assert(st != NULL);
	dependencies_file dp = {st,0,1};
	stream s_file = {
			string_type,
			memory_heap_tam_memory(get_stream_memory(),Tam_String),
			memory_heap_tam_memory(get_stream_memory(),Tam_String),
			file_stream_has_next,
			file_stream_next,
			get_value_sm(sizeof(dependencies_file), &dp)};
	return s_file;
}

void stream_free(stream * st) {
	free(st->state);
}
