/*
 * definitions.h
 *
 *  Created on: 18 ago. 2018
 *      Author: migueltoro
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define supplier(s) void * (* s)()
#define consumer(c) void (* c)(const void * e)
#define biconsumer(b) void (* b)(const void * e1, const void * e2)

#define predicate(p) boolean (* p)(const void * e)
#define bipredicate(p) boolean (* p)(const void * e1, const void * e2)
/*
 * A function that computes f(source), store the result end return this
*/
#define function(f) void * (* f)(void * result, const void * source)
#define bifunction(f) void * (* f)(void * result, const void * e1, const void * e2)

#define comparator(c) int (* c)(const void * e1, const void * e2)


#define int_function(h) int (* h)(const void * e)
#define long_function(h) int (* h)(const void * e)
#define double_function(h) double (* h)(const void * e)

#define to_int *(int*)
#define to_long *(long*)
#define to_float *(float*)
#define to_double *(double*)
#define to_char (char*)
#define to_optional *(optional*)

#endif /* DEFINITIONS_H_ */
