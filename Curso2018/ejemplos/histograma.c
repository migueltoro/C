/*
 * recursivos.c
 *
 *  Created on: 19 dic. 2019
 *      Author: migueltoro
 */


#include "histograma.h"

sol sol_zero(){
	sol r = {NULL,-1,-1,1000,-1,0};
	return r;
}

sol sol_of(list * ls, int inf, int sup, int min_index){
	int h = *(int *) list_get(ls,min_index);
	int a = (sup-inf)*h;
	sol r = {ls,inf,sup,h,min_index,a};
	return r;
}

int int_value(list * ls, int i){
	return *(int *) list_get(ls,i);
}

int min_index_2(list * ls, int i, int j){
	int r = i;
	int hi = *(int *) list_get(ls,i);
	int hj = *(int *) list_get(ls,j);
	if(hi < hj) r = i;
	else if(hi > hj) r = j;
	return r;
}

int min_index_3(list * ls, int i, int j, int k){
	int r = min_index_2(ls,i,j);
	return min_index_2(ls, r,k);
}

int ord_area(sol s1, sol s2){
	int r = 0;
	if(s1.a < s2.a) r = -1;
	else if(s1.a > s2.a) r = +1;
	return r;
}

sol max3_area(sol s1, sol s2, sol s3){
	sol r = s1;
	if(ord_area(s2,r) > 0) r = s2;
	if(ord_area(s3,r) > 0) r = s3;
	return r;
}

char * sol_tostring(sol s, char * mem){
	sprintf(mem,"(inf = %d, sup = %d, min_h = %d, min_index = %d, area = %d)",s.inf,s.sup,s.min_h,s.min_index,s.a);
	return mem;
}

sol centro(list * ls, int i, int j, int k);

sol histograma3(list * ls, int i, int j);

sol histograma0(list * ls) {
	int n = list_size(ls);
	sol amax = sol_zero();
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j <= n; j++) {
			int m = i;
			for (int k = i; k < j; k++) {
				m = min_index_2(ls,k,m);
			}
			sol e = sol_of(ls,i,j,m);
			if (ord_area(e, amax) > 0) amax = e;
		}
	}
	return amax;
}


sol histograma1(list * ls){
	int n = list_size(ls);
	sol em = sol_zero();
	for(int i = 0; i < n; i++){
		int m = i;
		for(int j = i+1; j <= n; j++){
			m = min_index_2(ls,j-1,m);
			sol e = sol_of(ls,i,j,m);
			if (ord_area(e,em) > 0) em = e;
		}
	}
	return em;
}

sol histograma2(list * ls){
	int n = list_size(ls);
	return histograma3(ls,0,n);
}

sol histograma3(list * ls, int i, int j){
	sol rm;
	if(j-i>1){
		int k = (j+i)/2;
		sol r1 = histograma3(ls,i,k);
		sol r2 = histograma3(ls,k,j);
		sol r3 = centro(ls,i,j,k);
		rm = max3_area(r1,r2,r3);
	} else if (j-i == 1) {
		rm = sol_of(ls,i,j,i);
	} else {
		rm = sol_zero();
	}

	return rm;
}



sol centro(list * ls, int i, int j, int k) {
        int i1 = k-1, j1 = k+1;
        int min_index = min_index_2(ls,i1,j1-1);
        sol amax = sol_zero();
        while(i1 >= i && j1 <= j) {
            min_index = min_index_3(ls,min_index,i1,j1-1);
            sol r = sol_of(ls,i1,j1,min_index);
            if(ord_area(r,amax) > 0) amax = r;
            if (i1 == i) j1++;
            else if (j1 == j) i1--;
            else {
                if (int_value(ls,i1-1) >= int_value(ls,j1))  i1--;
                else j1++;
            }
        }
        return amax;
}


void test_histograma(){
	char mem[100];
	int datos[] = {6,2,5,4,5,9,6,6,2,2,4,5,9,6,6,2,5,4,5,9,6,6,2,3,4,5,9,6};
	int n = sizeof(datos)/sizeof(int);
	printf("\n%d\n",n);
	list ls = list_of(datos,n,int_type);
	sol s0 = histograma0(&ls);
	printf("\n%s\n",sol_tostring(s0,mem));
	sol s1 = histograma1(&ls);
	printf("\n%s\n",sol_tostring(s1,mem));
	sol s2 = histograma2(&ls);
	printf("\n%s\n",sol_tostring(s2,mem));
}
