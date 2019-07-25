/*
 * dates.c
 *
 *  Created on: 7 nov. 2018
 *      Author: migueltoro
 */

#include "../types/dates.h"


time_t time_now(){
	return time(NULL);
}

time_t time_create_date(int day, int month, int year) {
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

time_t time_create_date_hour(int day, int month, int year, int hour, int minute, int second) {
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

time_t time_parse_date(char * text){
	int day;
	int month;
	int year;
	sscanf(text,"%d-%d-%d",&day,&month,&year);
	return time_create_date(day,month,year);
}

time_t * time_parse_out(time_t * out, char * text){
	int day;
	int month;
	int year;
	sscanf(text,"%d-%d-%d",&day,&month,&year);
	time_t t = time_create_date(day,month,year);
	* out = t;
	return out;
}

time_t time_parse_day_hour(char * text){
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
	sscanf(text,"%d-%d-%d %d:%d:%d",&day,&month,&year,&hour,&minute,&second);
	return time_create_date_hour(day,month,year,hour,minute,second);
}

time_t time_parse_hour(char * text){
	int hour;
	int minute;
	int second;
	time_t t = time_now();
	struct tm * r = localtime(&t);
	sscanf(text,"%d:%d:%d",&hour,&minute,&second);
	return time_create_date_hour(r->tm_mday,r->tm_mon+1,r->tm_year+1900,hour,minute,second);
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

double time_diff_seconds(time_t end, time_t start){
	return difftime(end,start);
}

double time_diff_minutes(time_t end, time_t start){
	return difftime(end,start)/60;
}

double time_diff_hours(time_t end, time_t start){
	return difftime(end,start)/3600;
}



char * dia_semana[] = {"Dom","Lun","Mar","Mie","Jue","Vie","Sab"};
char * meses[] = {"Ene","Feb","Mar","Abr","May","Jun","Jul","Ago","Sep","Oct","Nov","Dic"};

char * time_tostring(const void * p, char * mem){
	time_t * t = (time_t *) p;
	struct tm * r = localtime(t);
	sprintf(mem,"%02d-%02d-%4d %02d:%02d:%02d",r->tm_mday,r->tm_mon+1,r->tm_year+1900,
			r->tm_hour,r->tm_min,r->tm_sec);
	return mem;
}

char * time_all_tostring(const void * p, char * mem){
	time_t * t = (time_t *) p;
	struct tm * r = localtime(t);
	sprintf(mem,"%3s %2d de %3s de %4d == %02d:%02d:%02d",
			dia_semana[r->tm_wday],
			r->tm_mday+1,
			meses[r->tm_mon],
			r->tm_year+1900,
			r->tm_hour,
			r->tm_min,
			r->tm_sec);
	return mem;
}

char * time_date_tostring(const void * p, char * mem){
	time_t * t = (time_t *) p;
	struct tm * r = localtime(t);
	sprintf(mem,"%02d-%02d-%4d",r->tm_mday,r->tm_mon+1,r->tm_year+1900);
	return mem;
}

char * time_hours_tostring(const void * p, char * mem){
	time_t * t = (time_t *) p;
	struct tm * r = localtime(t);
	sprintf(mem,"%02d:%02d:%02d",r->tm_hour,r->tm_min,r->tm_sec);
	return mem;
}

bool time_equals(const void * p1, const void * p2){
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

void * time_copy(void * out, void * in){
	*(time_t *) out = *(time_t *) in;
	return out;
}

void * time_pointer_copy(void * out, void * in){
	*(time_t **) out = (time_t *) in;
	return out;
}


type time_type = {time_equals,time_tostring,time_naturalorder,time_parse_out,sizeof(time_t)};


bool pd(void * t){
	time_t e = time_create_date(1,1,1992);
	return time_naturalorder(t,&e) >0;
}

void * add(void * out, void * in){
	time_t e = *(time_t *) in;
	time_t * r = (time_t *) out;
	*r = time_add_days(e,90);
	return out;
}

void test_dates() {
	char mem[1000];
	time_t now = time_now();
	time_t t0 = time_minus_days(now,3);
	time_t t1 = time_create_date(2, 3, 1990);
	printf("%s\n", time_all_tostring(&now, mem));
	printf("%s\n", time_all_tostring(&t0, mem));
	printf("%s\n", time_all_tostring(&t1, mem));
	time_t a[] = {
			time_create_date(2, 3, 1991),
			time_create_date(1, 5, 1995),
			time_create_date(2, 9, 1989),
			time_create_date(2, 7, 2001),
			time_create_date(1, 1, 2019),
			time_create_date(3, 4, 2010),
			time_create_date(1, 5, 2013),
			time_create_date(2, 4, 1992),
			time_create_date(1, 5, 1996),
			time_create_date(5, 10, 1991),
			time_create_date(2, 4, 2002),
			time_create_date(1, 1, 2016),
			time_create_date(3, 1, 2011),
			time_create_date(1, 3, 2012)};
	list ls = list_of(a, 14, time_type);
	char * s = list_tostring(&ls, mem);
	printf("1: %s\n", s);
	list_sort(&ls, time_naturalorder);
	s = list_tostring(&ls, mem);
	printf("2: %s\n", s);
	list f = list_filter(&ls, pd,sizeof(time_t));
	s = list_tostring(&f, mem);
	printf("3: %s\n", s);
	list f2 = list_map(&ls,add,time_type);
	s = list_tostring(&f2, mem);
	printf("4: %s\n", s);
	char tt[] = "17-11-2018";
	time_t t = time_parse_date(tt);
	printf("%s\n",time_all_tostring(&t,mem));
	time_t t2 = time_parse_day_hour("17-11-2018  8:15:21");
	printf("%s\n",time_tostring(&t2,mem));
}
