/*
 * accumulators.c
 *
 *  Created on: 7 jul. 2019
 *      Author: migueltoro
 */

#include "../types/accumulators.h"


void * accumulate_left_e_r(iterable * st, void * base,void * result,
		void * (*add)(void * out, const void * e),
		bool isdone(void * in), void * (*f_result)(void * out, const void * in)) {

	while (iterable_has_next(st) && !isdone(base)) {
		void * e = iterable_next(st);
		add(base, e);
	}
	return f_result(result, base);
}

void * accumulate_left_r(iterable * st,
		void * base,
		void * result,
		void * (*add)(void * out, const void * e), void * (*f_result)(void * out, const void * in)) {

	while (iterable_has_next(st)) {
		void * e = iterable_next(st);
		add(base, e);
	}
	return f_result(result, base);
}

void * accumulate_left_e(iterable * st, void * base,
		void * (*add)(void * out, const void * e),
		bool isdone(void * in)) {

	while (iterable_has_next(st) && !isdone(base)) {
		void * e = iterable_next(st);
		add(base, e);
	}
	return base;
}

void * accumulate_left(iterable * st, void * base,
		void * (*add)(void * out, const void * e)) {

	while (iterable_has_next(st)) {
		void * e = iterable_next(st);
		add(base, e);
	}
	return base;
}


void accumulate_right_private(iterable * st, void * base, int size_element,
		void * (*add)(void * out, const void * e)) {
	if (iterable_has_next(st)) {
		char se[size_element];
		void * e = iterable_next(st);
		copy(se, e, size_element);
		accumulate_right_private(st, base, size_element, add);
		add(base, se);
	}
}

void * accumulate_right(iterable * st, void * base, int size_element,
		void * (*add)(void * out, const void * e)) {
	accumulate_right_private(st,base,size_element,add);
	return base;
}


void * accumulate_right_r(iterable * st, void * base, void * result, int size_element,
		void * (*add)(void * out, const void * e),
		void * (f_result)(void * out, const void * e)) {
	accumulate_right_private(st,base,size_element,add);
	return f_result(result,base);
}


void * reduce_left(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e)) {
	bool first = true;
	while (iterable_has_next(st)) {
		void * e = iterable_next(st);
		if (first) {
			copy(base, e, size_base);
			first = false;
		} else {
			add(base, e);
		}
	}
	return base;
}

void * reduce_left_e(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *)) {
	bool first = true;
	while (iterable_has_next(st)) {
		void * e = iterable_next(st);
		if (first) {
			copy(base, e, size_base);
			first = false;
		} else {
			add(base, e);
			if (isdone(base)) break;
		}
	}
	return base;
}


void reduce_right_private(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool * first) {
	if (iterable_has_next(st)) {
		char se[size_base];
		void * e = iterable_next(st);
		copy(se, e, size_base);
		reduce_right_private(st, base, size_base, add, first);
		if (*first) {
			copy(base, e, size_base);
			* first = false;
		} else {
			add(base, se);
		}
	}
}

void * reduce_right(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e)) {
	bool first = true;
	reduce_right_private(st, base, size_base, add, &first);
	return base;
}

void reduce_right_e_private(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *),
		bool * first) {
	if (iterable_has_next(st)) {
		char se[size_base];
		void * e = iterable_next(st);
		copy(se, e, size_base);
		reduce_right_private(st, base, size_base, add, first);
		if (*first) {
			copy(base, e, size_base);
			*first = false;
		} else {
			if (!isdone(base)) add(base, se);
		}
	}
}

void * reduce_right_e(iterable * st, void * base, int size_base,
		void * (*add)(void * out, const void * e), bool isdone(void *)) {
	bool first = true;
	reduce_right_e_private(st, base, size_base, add, isdone, &first);
	return base;
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

void * add_estadisticos(estadisticos * est, const void * in){
	double e = *(double *) in;
	est->num = est->num+1;
	est->sum = est->sum + e;
	est->sum_cuadrados = est->sum_cuadrados + e*e;
	est->max = MAX(est->max,e);
	est->min = MIN(est->min,e);
	return est;
}

void * result_estadisticos(estadisticos * est_out, const estadisticos * est_in){
	est_out->num = est_in->num;
	est_out->sum = est_in->sum;
	est_out->sum_cuadrados = est_in->sum_cuadrados;
	est_out->max = est_in->max;
	est_out->min = est_in->min;
	est_out->media = est_in->sum/est_in->num;
	est_out->varianza = est_in->sum_cuadrados/est_in->num - est_out->media*est_out->media;
	est_out->desviacion_tipica = sqrt(est_out->varianza);
	return est_out;
}

char * estadisticos_tostring(void * in, char * mem){
	estadisticos e = *(estadisticos *) in;
	sprintf(mem,
	  "(num = %d,sum = %.2lf,sum_cuadrados = %.2lf,max = %.2lf,min = %.2lf,media = %.2lf,varianza = %.2lf,desviacion_tipica = %.2lf)",
	  e.num,e.sum,e.sum_cuadrados,e.max,e.min,e.media,e.varianza,e.desviacion_tipica);
	return mem;
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

double iterable_sum(iterable * st) {
	double r = 0;
	while (iterable_has_next(st)) {
		void * e = iterable_next(st);
		r = r+*(double *) e;
	}
	return r;
}

int iterable_size(iterable * st) {
	int r = 0;
	while (iterable_has_next(st)) {
		iterable_next(st);
		r = r+1;
	}
	return r;
}

double iterable_average(iterable * st) {
	double r = 0;
	int n = 0;
	while (iterable_has_next(st)) {
		void * e = iterable_next(st);
		r =  r+*(double *) e;
		n = n+1;
	}
	check_argument(n != 0, __FILE__, __LINE__, "el número de elementos es cero");
	return r/n;
}

void * resto17(int * out, int * in){
	*out = (*in)%17;
	return out;
}

char * pair_long_double_tostring(const pair * in, char * mem){
	char m[Tam_String];
	sprintf(mem,"(%s,%s)",long_tostring(in->key,m),double_tostring(in->value,m));
	return mem;
}

char * pair_int_long_tostring(const pair * in, char * mem){
	char m[Tam_String];
	sprintf(mem,"(%s,%s)",int_tostring(in->key,m),long_tostring(in->value,m));
	return mem;
}


char * pair_long_list_tostring(const pair * in, char * mem){
	char m[Tam_String];
	sprintf(mem,"(%s,%s)",long_tostring(in->key,m),list_tostring(in->value,m));
	return mem;
}

bool esmultiplo17(const long *in){
	return (*in)%17 == 0;
}

bool esmultiplo44(const long *in){
	return (*in)%44 == 0;
}

long * long_sum(long * out, long * in){
	*out = *out + *in;
	return out;
}

long * long_max(long * out, long * in){
	*out = MAX(*out,*in);
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
	estadisticos est= estadisticos_ini;
	estadisticos est_r;
	void * e = accumulate_left_r(&st,&est,&est_r,add_estadisticos,result_estadisticos);
	printf("3:  \n%s\n",estadisticos_tostring(e,mem));
	st = iterable_range_double(4,500,3);
	st = iterable_range_long(4,500,3);
	bool r = iterable_all(&st,esmultiplo17);
	printf("5:  \n%s\n",bool_tostring(r));
	st = iterable_range_long(4,500,3);
	r = iterable_any(&st,esmultiplo17);
	printf("6:  \n%s\n",bool_tostring(r));
	st = iterable_range_long(7,500,3);
	long r1 = *(long *) iterable_first(&st,esmultiplo17);
	printf("7:  \n%ld\n",r1);
	double r7;
	st = iterable_range_long(7, 500, 3);
	reduce_left(&st,&r7,sizeof(double),long_sum);
	printf("8:  \n%ld\n", r7);
	st = iterable_range_long(7, 500, 3);
	reduce_right(&st,&r7,sizeof(double),long_sum);
	printf("8.1:  \n%ld\n", r7);
	st = iterable_range_long(7, 500, 3);
	reduce_left(&st,&r7,sizeof(double),long_max);
	printf("9:  \n%ld\n", r7);
	st = iterable_range_long(7, 500, 3);
	reduce_right(&st,&r7,sizeof(double),long_max);
	printf("9.1:  \n%ld\n", r7);
	char text[] = "El    Gobierno abre la puerta a no;llevar los Presupuestos.Generales de 2019 al Congreso si no logra los apoyos suficientes para sacarlos adelante. Esa opción que ya deslizaron fuentes próximas al presidente la ha confirmado la portavoz, Isabel Celaá, en la rueda de prensa posterior a la reunión del gabinete en la que ha asegurado que el Consejo de Ministras tomará la decisión sobre llevar o no las cuentas públicas al Parlamento una vez concluyan las negociaciones de la ministra María Jesús Montero. ";
	iterable p3 = split_iterable_pchar(text," ;.");
	string emp = string_empty();
	void * sr = accumulate_left(&p3,&emp,string_add_pchar);
	printf("10: %s\n",string_tostring(sr,mem));
	p3 = split_iterable_pchar(text," ;.");
	emp = string_empty();
	sr = accumulate_right(&p3,&emp,30,string_add_pchar);
	printf("11: %s\n",string_tostring(sr,mem));
}

