/*
 * dates.c
 *
 *  Created on: 7 nov. 2018
 *      Author: migueltoro
 */

#include "dates.h"


time_t time_now(){
	return time(NULL);
}

time_t time_create(int day, int month, int year) {
	struct tm str;
	time_t r;
	str.tm_year = year - 1900;
	str.tm_mon = month - 1;
	str.tm_mday = day;
	str.tm_hour = 0;
	str.tm_min = 0;
	str.tm_sec = 0;
	str.tm_isdst = 0;
	r = mktime(&str);
	return r;
}

time_t time_create_hour(int day, int month, int year, int hour, int minute, int second) {
	struct tm str;
	time_t r;
	str.tm_year = year - 1900;
	str.tm_mon = month - 1;
	str.tm_mday = day;
	str.tm_hour = hour;
	str.tm_min = minute;
	str.tm_sec = second;
	str.tm_isdst = 0;
	r = mktime(&str);
	return r;
}

time_t time_parse(char * text){
	int day;
	int month;
	int year;
	sscanf(text,"%d-%d-%d",&day,&month,&year);
	return time_create(day,month,year);
}

time_t time_parse_hour(char * text){
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
	sscanf(text,"%d-%d-%d %d:%d:%d",&day,&month,&year,&hour,&minute,&second);
	return time_create_hour(day,month,year,hour,minute,second);
}

struct tm * time_calendar(time_t time){
	return localtime(&time);
}

time_t time_add_days(time_t date, int days) {
	struct tm * r = localtime(&date);
	r->tm_mday = r->tm_mday + days;
	return mktime(r);
}

time_t time_add_months(time_t date, int months) {
	struct tm * r = localtime(&date);
	r->tm_mon = r->tm_mon + months;
	return mktime(r);
}

time_t time_add_years(time_t date, int years) {
	struct tm * r = localtime(&date);
	r->tm_year = r->tm_year + years;
	return mktime(r);
}

time_t time_minus_days(time_t date, int days) {
	struct tm * r = localtime(&date);
	r->tm_mday = r->tm_mday - days;
	return mktime(r);
}

time_t time_minus_months(time_t date, int months) {
	struct tm * r = localtime(&date);
	r->tm_mon = r->tm_mon - months;
	return mktime(r);
}

time_t time_minus_years(time_t date, int years) {
	struct tm * r = localtime(&date);
	r->tm_year = r->tm_year - years;
	return mktime(r);
}


char * time_tostring(const void * p, char * mem){
	return (char *)remove_eol(ctime((time_t *)p));
}

int time_equals(const void * p1, const void * p2){
	time_t t1 = *(time_t *) p1;
	time_t t2 = *(time_t *) p2;
	return t1 == t2;
}

int time_naturalorder(const void * p1,const  void * p2){
	time_t t1 = *(time_t *) p1;
	time_t t2 = *(time_t *) p2;
	int d = difftime(t2,t1);
	int r;
	if(d>0) r = -1;
	else if(d<0) r= +1;
	else r= 0;
	return r;
}


bool pd(void * t){
	time_t e = time_create(1,1,1992);
	return time_naturalorder(t,&e) >0;
}

memory_heap hp;

void * add(void * t){
	time_t e = *(time_t *)t;
	time_t r = time_add_days(e,90);
	return to_data(&r,sizeof(time_t),&hp);
}

void test_dates() {
	hp = memory_heap_create();
	char mem[1000];
	time_t now = time_now();
	time_t t1 = time_create(2, 3, 1990);
	printf("%s\n", time_tostring(&now, NULL));
	printf("%s\n", time_tostring(&t1, NULL));
	time_t a[] = {
			time_create(2, 3, 1991),
			time_create(1, 5, 1995),
			time_create(2, 9, 1989),
			time_create(2, 7, 2001),
			time_create(1, 1, 2019),
			time_create(3, 4, 2010),
			time_create(1, 5, 2013),
			time_create(2, 4, 1992),
			time_create(1, 5, 1996),
			time_create(5, 10, 1991),
			time_create(2, 4, 2002),
			time_create(1, 1, 2016),
			time_create(3, 1, 2011),
			time_create(1, 3, 2012)};
	alist ls = alist_of(a, 14, sizeof(time_t));
	char * s = alist_tostring(&ls, time_tostring, mem);
	printf("1: %s\n", s);
	alist_sort(&ls, time_naturalorder);
	s = alist_tostring(&ls, time_tostring, mem);
	printf("2: %s\n", s);
	alist f = alist_filter(&ls, pd);
	s = alist_tostring(&f, time_tostring, mem);
	printf("3: %s\n", s);
	alist f2 = alist_map(&ls, add);
	s = alist_tostring(&f2, time_tostring, mem);
	printf("4: %s\n", s);
	char tt[] = "17-11-2018";
	time_t t = time_parse(tt);
	printf("%s\n",time_tostring(&t,mem));
	time_t t2 = time_parse_hour("17-11-2018  8:15:21");
	printf("%s\n",time_tostring(&t2,mem));
	memory_heap_free(&hp);
}
