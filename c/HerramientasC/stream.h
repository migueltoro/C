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



typedef struct st {
	type state_type;
	void * state;
	void * auxiliary_state;
	bool (*has_next)(struct st * stream,void * dependencies);
	void * (*next)(struct st * stream, void * dependencies);
	void * (*see_next)(struct st * stream, void * dependencies);
	void * dependencies;
} stream;

int stream_equals(const void * e1, const void * e2);
//stream stream_create(type state_type,void * initial, bool (*has_next)(stream *,void *),
//			void * (*next)(stream *,void *), void * dependencies);
stream stream_map(stream * st, type type_map, void * (*map_function)(void * out, void * in));
stream stream_filter(stream * st, bool (*map_filter)(void * in));
stream stream_range_int(long a, long b, long c);
stream stream_iterate(type element_type, void * initial_value, bool (*hash_next)(void * element),
		void * (*next)(void * state));
stream stream_iterate_long(long initial_value, bool (*hash_next)(long), long (*next)(long));
stream stream_iterate_double(double initial_value, bool (*hash_next)(double), double (*next)(double state));
stream stream_iterate_tuple2(tuple2 initial_value, bool (*hash_next)(tuple2), tuple2 (*next)(tuple2));
stream file_stream(char * file);
void stream_to_buffer(string_buffer * buffer, stream * stream);

int stream_has_next(stream * st);
void * stream_see_next(stream * st);
void * stream_next(stream * st);



void stream_free(stream * st);

void * get_mem_sm(int size);
void * get_int_sm(int value);
void * get_long_sm(long value);
void * get_value_sm(int size, void * value);

void stream_memory_clear();

extern type stream_type;


#endif /* STREAM_H_ */
