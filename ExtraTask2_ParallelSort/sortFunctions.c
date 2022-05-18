#include <stdio.h>
#include <stdlib.h>

#include"sortFunctions.h"

void mergeUp(int *array, size_t arraySize) {
	int step = arraySize / 2, i, j, k, temp;
	while (step > 0) {
		for (i = 0; i < arraySize; i += step * 2) {
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

void mergeDown(int *array, size_t arraySize) {
	int step = arraySize / 2, i, j, k, temp;
	while (step > 0) {
		for (i = 0; i < arraySize; i += step * 2) {
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

void sortSequential(int *array, size_t arraySize) {
	int k, i;
	for (k = 2; k <= arraySize; k *= 2) {
		for (i = 0; i < arraySize;) {
			mergeUp((array + i), k);
			mergeDown((array + i + k), k);
			i += k * 2;
		}
	}
}