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
	int (*has_next)(void * state,void * dependencies);
	void * (*next)(void * state, void * dependencies);
	void * dependencies;
} stream;

int stream_equals(const void * e1, const void * e2);
stream stream_create(type actual_type, void * initial, int (*has_next)(void *,void *),
			void * (*next)(void *,void *), void * dependencies);
stream range_int(int a, int b, int c);
stream file_stream(char * file);
stream stream_map(stream st, type type_map, void * (*map_function)(void * target, void * source));
stream stream_filter(stream st, int (*map_filter)(void *));
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
