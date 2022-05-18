#include <stdio.h>
#include <stdlib.h>

#include"sortFunctions.h"

void mergeUp(int *array, size_t n) {
	int step = n / 2, i, j, k, temp;
	while (step > 0) {
		for (i = 0; i < n; i += step * 2) {
			for (j = i, k = 0; k < step; j++, k++) {
				if (array[j] > array[j+step]) {
					// Swapping
					temp = array[j];
					array[j] = array[j+step];
					array[j+step] = temp;
				}
			}
		}
		step /= 2;
	}
}

void mergeDown(int *array, size_t n) {
	int step = n / 2, i, j, k, temp;
	while (step > 0) {
		for (i = 0; i < n; i += step * 2) {
			for (j = i, k = 0; k < step; j++, k++) {
				if (array[j] < array[j+step]) {
					// Swapping
					temp = array[j];
					array[j] = array[j+step];
					array[j+step] = temp;
				}
			}
		}
		step /= 2;
	}
}