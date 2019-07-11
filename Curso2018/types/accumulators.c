/*
 * accumulators.c
 *
 *  Created on: 7 jul. 2019
 *      Author: migueltoro
 */

#include "../types/accumulators.h"

bool is_done_false_d(const void * base, void * dependencies){
	return false;
}

bool is_done_false(const void * base){
	return false;
}

void * result_identity(void * result, const void * base, void * dependencies){
	return result;
}

accumulator create_accumulator(
		int size_state,
		int size_result,
		void * initial_value,
		void * (*add)(void * base, const void * value, void * dependencies),
		void * (*result)(void * rs, const void * base, void * dependencies),
		bool (*isdone)(const void * base, void * dependencies),
		int size_dependencies){
	void * d = size_dependencies>0 ? malloc(size_dependencies): NULL;
	accumulator ac = {size_state,size_result,malloc(size_state),malloc(size_result),add,result,isdone,d};
	copy(ac.state,initial_value,size_state);
	return ac;
}

void * accumulate_left(iterable * st, accumulator * ac){
	while(iterable_has_next(st) && !ac->isdone(ac->state,ac->dependencies)){
		void * e = iterable_next(st);
		ac->add(ac->state,e,ac->dependencies);
	}
	ac->result(ac->result_value,ac->state,ac->dependencies);
	return ac->result_value;
}

void accumulate_right_private(iterable * st, accumulator * ac){
	if(iterable_has_next(st)){
		void * value = iterable_next(st);
		void * vc = malloc(st->size_state);
		copy(vc,value,st->size_state);
		accumulate_right_private(st,ac);
		if(!ac->isdone(ac->state,ac->dependencies))
			ac->add(ac->state,vc,ac->dependencies);
		free(vc);
	}
}

void * accumulate_right(iterable * st, accumulator * ac){
	accumulate_right_private(st,ac);
	ac->result(ac->result_value,ac->state,ac->dependencies);
	return ac->result_value;
}

accumulator accumulator_reduce(
		int size_element,
		void * first_element,
		void * (*f)(void * out, const void * in),
		bool (*isdone)(const void * in));

void * reduce_left(iterable * st,void * (*f)(void * out, const void * in)){
	return reduce_left_e(st,f,is_done_false);
}

void * reduce_left_e(iterable * st,
		void * (*f)(void * out, const void * in),
		bool (*isdone)(const void * in)){
	bool first = true;
	accumulator ac = accumulator_reduce(st->size_state,NULL,f,isdone);
	while(iterable_has_next(st) && !ac.isdone(ac.state,ac.dependencies)){
		void * e = iterable_next(st);
		if(first){
			copy(ac.state,e,ac.size_state);
			first = false;
		} else {
			ac.add(ac.state,e,ac.dependencies);
		}
	}
	ac.result(ac.result_value,ac.state,ac.dependencies);
	return ac.result_value;
}

void reduce_right_private(iterable * st, accumulator * ac, bool * first) {
	if (iterable_has_next(st)) {
		void * value = iterable_next(st);
		void * vc = malloc(st->size_state);
		copy(vc, value, st->size_state);
		accumulate_right_private(st, ac);
		if(*first){
			copy(ac->state,vc,ac->size_state);
			*first = false;
		} else {
			if (!ac->isdone(ac->state, ac->dependencies))
				ac->add(ac->state, vc, ac->dependencies);
		}
		free(vc);
	}
}


void * reduce_right(iterable * st,void * (*f)(void * out, const void * in)) {
	return reduce_right_e(st,f,is_done_false);
}

void * reduce_right_e(iterable * st,
		void * (*f)(void * out, const void * in),
		bool (*isdone)(const void * in)) {
	accumulator ac = accumulator_reduce(st->size_state,NULL,f,isdone);
	bool first;
	reduce_right_private(st, &ac,&first);
	return ac.result_value;
}


void * iterable_min(iterable * st, int (*comparator)(const void * out, const void * in)){
	void * r = NULL;
	while(iterable_has_next(st)){
		void * next = iterable_next(st);
		if(r == NULL || comparator(next,r) < 0) r = next;
	}
	return r;
}

void * iterable_max(iterable * st, int (*comparator)(const void * out, const void * in)){
	void * r = NULL;
	while(iterable_has_next(st)){
		void * next = iterable_next(st);
		if(r == NULL || comparator(next,r) > 0) r = next;
	}
	return r;
}

list iterable_to_list(iterable * st, type type_element){
	list r = list_empty(type_element);
	while(iterable_has_next(st)){
		char * s = iterable_next(st);
		list_add(&r,s);
	}
	return r;
}

set iterable_to_set(iterable * st, type type_element) {
	set r = set_empty(type_element);
	while (iterable_has_next(st)) {
		char * s = iterable_next(st);
		set_add(&r, s);
	}
	return r;
}

hash_table iterable_counting(iterable * st,
		void * (*f_key)(void * out, void * in),
		type key_type){
	char mem[20];
	int uno = 1;
	hash_table ht = hash_table_empty(key_type,sizeof(int));
	while(iterable_has_next(st)){
		void * next = iterable_next(st);
		void * key = f_key(mem,next);
		if(hash_table_contains(&ht,key)){
			void * n = hash_table_get(&ht,key);
			*(int *)n = (*(int *)n)+1;
		} else {
			hash_table_put(&ht,key,&uno);
		}
	}
	return ht;
}

hash_table iterable_grouping(iterable * st,
		void * (*f_key)(void * out, void * in),
		type key_type,
		type value_type){
	char mem[20];
	hash_table ht = hash_table_empty(key_type,sizeof(list));
	while(iterable_has_next(st)){
		void * next = iterable_next(st);
		void * key = f_key(mem,next);
		if(hash_table_contains(&ht,key)){
				list * lse = (list *) hash_table_get(&ht,key);
				list_add(lse,next);
		} else {
				list ls = list_empty(value_type);
				list_add(&ls,next);
				hash_table_put(&ht,key,&ls);
		}
	}
	return ht;
}

estadisticos estadisticos_ini = {0,0,0,-DBL_MAX,DBL_MAX,0,0,0};

void * add_estadisticos(void * out, const void * in, void * dependencies){
	estadisticos * est = (estadisticos *) out;
	double e = *(double *) in;
	est->num = est->num+1;
	est->sum = est->sum + e;
	est->sum_cuadrados = est->sum_cuadrados + e*e;
	est->max = MAX(est->max,e);
	est->min = MIN(est->min,e);
	return out;
}

void * result_estadisticos(void * out, const void * in, void * dependencies){
	estadisticos est_in = *(estadisticos *) in;
	estadisticos * est_out = (estadisticos *) out;
	est_out->num = est_in.num;
	est_out->sum = est_in.sum;
	est_out->sum_cuadrados = est_in.sum_cuadrados;
	est_out->max = est_in.max;
	est_out->min = est_in.min;
	est_out->media = est_in.sum/est_in.num;
	est_out->varianza = est_in.sum_cuadrados/est_in.num - est_out->media*est_out->media;
	est_out->desviacion_tipica = sqrt(est_out->varianza);
	return out;
}

char * estadisticos_tostring(void * in, char * mem){
	estadisticos e = *(estadisticos *) in;
	sprintf(mem,
	  "(num = %d,sum = %.2lf,sum_cuadrados = %.2lf,max = %.2lf,min = %.2lf,media = %.2lf,varianza = %.2lf,desviacion_tipica = %.2lf)",
	  e.num,e.sum,e.sum_cuadrados,e.max,e.min,e.media,e.varianza,e.desviacion_tipica);
	return mem;
}

accumulator accumulator_estadisticos() {
	accumulator ac = create_accumulator(
			sizeof(estadisticos),
			sizeof(estadisticos),
			&estadisticos_ini,
			add_estadisticos,
			result_estadisticos,
			is_done_false_d,
			0);
	return ac;
}


bool iterable_all(iterable * st, bool (*p)(const void * in)){
	bool r = true;
	while(iterable_has_next(st) && r) {
		void * e = iterable_next(st);
		r = p(e);
	}
	return r;
}

bool iterable_any(iterable * st, bool (*p)(const void * in)) {
	bool r = false;
	while (iterable_has_next(st) && !r) {
		void * e = iterable_next(st);
		r = p(e);
	}
	return r;
}

void * iterable_first(iterable * st, bool (*p)(const void * in)) {
	void * r = NULL;
	while (iterable_has_next(st) && r == NULL) {
		void * e = iterable_next(st);
		if(p(e)) r = e;
	}
	return r;
}


typedef struct{
	void * (*f)(void * out, const void * in);
	bool (*isdone)(const void * in);
}reduce_dependencies;

void * add_reduce(void * out, const void * in, void * dependencies){
	reduce_dependencies * dr = (reduce_dependencies * ) dependencies;
	dr->f(out,in);
	return out;
}

bool isdone_reduce(const void * in, void * dependencies){
	reduce_dependencies * dr = (reduce_dependencies * ) dependencies;
	return dr->isdone(in);
}

accumulator accumulator_reduce(int size_element, void * first_element,
		void * (*f)(void * out, const void * in),
		bool (*isdone)(const void * in)) {
	accumulator ac = create_accumulator(size_element, 0, first_element,
			add_reduce, result_identity, isdone_reduce,
			sizeof(reduce_dependencies));
	ac.result_value = ac.state;
	((reduce_dependencies *) ac.dependencies)->f = f;
	((reduce_dependencies *) ac.dependencies)->isdone = isdone;
	return ac;
}


void * resto17(void * out, void * in){
	int e = to_int(in);
	int r = e%7;
	*(int *) out = r;
	return out;
}

char * pair_long_double_tostring(const void * in, char * mem){
	pair * t = (pair *) in;
	char m[Tam_String];
	sprintf(mem,"(%s,%s)",long_tostring(t->key,m),double_tostring(t->value,m));
	return mem;
}

char * pair_int_long_tostring(const void * in, char * mem){
	pair * t = (pair *) in;
	char m[Tam_String];
	sprintf(mem,"(%s,%s)",int_tostring(t->key,m),long_tostring(t->value,m));
	return mem;
}


char * pair_long_list_tostring(const void * in, char * mem){
	pair * t = (pair *) in;
	char m[Tam_String];
	sprintf(mem,"(%s,%s)",long_tostring(t->key,m),list_tostring(t->value,m));
	return mem;
}

bool esmultiplo17(const void *in){
	long e = *(long*)in;
	return e%17 == 0;
}

bool esmultiplo44(const void *in){
	long e = *(long*)in;
	return e%44 == 0;
}

void * long_sum(void * out, const void * in){
	long * e = (long *) in;
	long * s = (long *) out;
	*s = *s + *e;
	return out;
}

void * string_concat(void * out, const void * in){
	char * e = (char *) in;
	char * s = (char *) out;
	strcat(s,e);
	return out;
}

void test_accumulators(){
	char mem[2000];
	iterable st = iterable_range_long(4,500,3);
	hash_table ht = iterable_counting(&st,resto17,int_type);
	char * s = hash_table_items_tostring(&ht,pair_int_long_tostring,mem);
	printf("1:  \n%s\n\n",s);
	st = iterable_range_long(4,500,3);
	hash_table ht2 = iterable_grouping(&st,resto17,int_type,long_type);
	iterable it = hash_table_items_iterable(&ht2);
	char * s2 = iterable_tostring_sep(&it,pair_long_list_tostring,"\n","__________________\n","\n_______________\n",mem);
	printf("2:  \n%s",s2);
	st = iterable_range_double(4,500,3);
	accumulator a = accumulator_estadisticos();
	estadisticos * e = (estadisticos *) accumulate_left(&st,&a);
	printf("3:  \n%s\n",estadisticos_tostring(e,mem));
	st = iterable_range_double(4,500,3);
	e = (estadisticos *) accumulate_right(&st,&a);
	printf("4:  \n%s\n",estadisticos_tostring(e,mem));
	st = iterable_range_long(4,500,3);
	bool r = iterable_all(&st,esmultiplo17);
	printf("5:  \n%s\n",bool_tostring(r));
	st = iterable_range_long(4,500,3);
	r = iterable_any(&st,esmultiplo17);
	printf("6:  \n%s\n",bool_tostring(r));
	st = iterable_range_long(7,500,3);
	long r1 = *(long *) iterable_first(&st,esmultiplo17);
	printf("7:  \n%ld\n",r1);
	st = iterable_range_long(7, 500, 3);
	r1 = *(long *) reduce_left(&st,long_sum);
	printf("8:  \n%ld\n", r1);
	st = iterable_range_long(7, 500, 3);
	r1 = *(long *) reduce_right(&st,long_sum);
	printf("9:  \n%ld\n", r1);
	char delimiters[] = " ,;.";
	char text[] = "El Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	char text2[] = "El Gobierno a";
	iterable sp = split_iterable(text2,delimiters);
	char * ss = (char *) reduce_left(&sp,string_concat);
	printf("10:  \n%s\n",ss);
	sp = split_iterable(text,delimiters);
	ss = (char *) reduce_right(&sp,string_concat);
	printf("11:  \n%s\n",ss);
}
