/*
 * generator.c
 *
 *  Created on: 25 ago. 2018
 *      Author: migueltoro
 */


#include "generator.h"

bool generator_stream_has_next(stream * current_stream, void * dependencies);
void * generator_stream_see_next(stream * current_stream, void * dependencies);
void * generator_stream_next(stream * current_stream, void * dependencies);

typedef struct {
	generator * g;
	bool is_done;
	bool has_next;
}dependencies_ge_stream;

bool generator_stream_has_next(stream * current_stream, void * dependencies) {
	dependencies_ge_stream * d = (dependencies_ge_stream *) dependencies;
	if (!(d->is_done)) {
		d->is_done = true;
		if (d->g->iterate_function(d->g)){
			d->has_next = true;
			copy(d->g->values_type, current_stream->state,d->g->values);
		} else {
			d->has_next = false;
		}
	}
return d->has_next;
}

void * generator_stream_see_next(stream * current_stream, void * dependencies){
    return current_stream->state;
}

void * generator_stream_next(stream * current_stream, void * dependencies){
	dependencies_ge_stream * dp = (dependencies_ge_stream *) dependencies;
	dp->is_done = false;
	return current_stream->state;
}

stream generator_stream(generator * g){
	dependencies_ge_stream dp = {g,false,false};

	stream new_st = {
			g->values_type,
			get_mem_sm(g->values_type->size_type),
			get_mem_sm(g->values_type->size_type),
			generator_stream_has_next,
			generator_stream_next,
			generator_stream_see_next,
			get_value_sm(sizeof(dependencies_ge_stream), &dp)
	};
	return new_st;
}

