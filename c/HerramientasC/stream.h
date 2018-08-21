/*
 * stream.h
 *
 *  Created on: 9 ago. 2018
 *      Author: migueltoro
 */

#ifndef STREAM_H_
#define STREAM_H_


#include "basic_types.h"
#include "string_buffer.h"
#include "memory_heap.h"



typedef struct {
	type state_type;
	void * state;
	bool (*has_next)(void * state,void * dependencies);
	void * (*next)(void * state, void * dependencies);
	void * dependencies;
} stream;

int stream_equals(const void * e1, const void * e2);
stream stream_create(type actual_type, void * initial, bool (*has_next)(void *,void *),
			void * (*next)(void *,void *), void * dependencies);
stream stream_range_int(int a, int b, int c);
stream stream_iterate(type element_type, void * initial_value, bool (*hash_next)(void * element),
		void * (*next)(void * state));
stream stream_iterate_int(int initial_value, bool (*hash_next)(int),int (*next)(int));
stream stream_iterate_double(double initial_value, bool (*hash_next)(double), double (*next)(double state));
stream stream_iterate_tuple2_int(tuple2_int initial_value, bool (*hash_next)(tuple2_int), tuple2_int (*next)(tuple2_int));
stream file_stream(char * file);
stream stream_map(stream st, type type_map, void * (*map_function)(void * target, void * source));
stream stream_filter(stream st, bool (*map_filter)(void *));
void stream_to_buffer(string_buffer * buffer, const stream);

int stream_has_next(stream st);
void * stream_next(stream st);



void stream_free(stream * st);

void * get_mem_sm(int size);
void * get_int_sm(int value);
void * get_long_sm(long value);
void * get_value_sm(int size, void * value);
void stream_memory_clear();

extern type stream_type;


#endif /* STREAM_H_ */
