/*
 * library.c
 *
 *  Created on: 15 ago. 2018
 *      Author: migueltoro
 */


#include "library.h"


void print_array(string_buffer * buffer, void **b, int low, int height, type type){
	char pm[256];
	for(int i = low; i < height; i++) {
			string_buffer_add(buffer,type.tostring(pm,b[i]));
	}
	string_buffer_close(buffer);
}

int partition(void **arr, int low, int hight, int (*compare)(const void *, const void *)) {

	int leftIndex = low + 1;
	int rightIndex = hight-1;
	while (1) {
		while (compare(arr[leftIndex], arr[low]) == -1) {
			leftIndex++;
			if (leftIndex >= hight-1) break;
		}

		while (compare(arr[rightIndex], arr[low]) >= 0) {
			rightIndex--;
			if (rightIndex == low) break;
		}

		if (leftIndex >= rightIndex) break;

		void *temp = arr[leftIndex];
		arr[leftIndex] = arr[rightIndex];
		arr[rightIndex] = temp;

	}

	void *temp = arr[low];
	arr[low] = arr[rightIndex];
	arr[rightIndex] = temp;

	return rightIndex;
}

void generic_qsort(void **arr, int low, int hight, int (*compare)(const void *, const void*)) {

	if (hight-low <= 1) return;

	//Situa el pivot en su posicion. Siendo p la posicion del pivote. A la izquierda del pivote menores. A
	//la derecha mayores o iguales
	int p = partition(arr, low, hight, compare);

	generic_qsort(arr, low, p, compare);
	generic_qsort(arr, p + 1, hight, compare);
}


