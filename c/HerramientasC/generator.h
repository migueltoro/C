/*
 * generator.h
 *
 *  Created on: 24 ago. 2018
 *      Author: migueltoro
 *
 *      Adaptado de https://gist.github.com/laindir
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "basic_types.h"
#include "stream.h"

#ifndef GENERATOR_H_
#define GENERATOR_H_

//#define start(generator) switch(generator) { case 0:;
#define START(gg) switch(gg->state) { case 0:
//#define finish default:; }
#define FINISH break; default:; }
/*save state and return value*/
//#define yield(state,value) do { state = __LINE__; return (value); case __LINE__:; } while (false)
#define YIELD(gg) do {gg->state = __LINE__; return (true); case __LINE__:; } while (false)


#define GG_VALUE(gg,values_type,value) ((values_type *) gg->values)->value



typedef struct p_p {
    int state;
    bool (*iterate_function)(struct p_p *);
    void * values;
    type * values_type;
    void * parameters;
} generator;

generator create( bool (*iterate_function)(generator *), type value_tpe, void *);

stream generator_stream(generator * g);

#endif /* GENERATOR_H_ */
