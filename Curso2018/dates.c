/*
 * dates.c
 *
 *  Created on: 7 nov. 2018
 *      Author: migueltoro
 */

#include "dates.h"


time_t now_time(){
	return time(NULL);
}

time_t create_time(int day, int month, int year) {
	struct tm str;
	time_t r;
	str.tm_year = year - 1900;
	str.tm_mon = month;
	str.tm_mday = day;
	str.tm_hour = 10;
	str.tm_min = 0;
	str.tm_sec = 0;
	str.tm_isdst = 0;
	r = mktime(&str);
	return r;
}

struct tm * calendar(time_t time){
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
