#include <stdio.h>
#include <stdlib.h>

#include"arrayFunctions.h"

void arrayPrint(int *array, size_t n) {
	size_t i;
	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void arrayInit(int *array, size_t n) {
	size_t i;
	for (i = 0; i < n; i++) {
		array[i] = i + 1;
	}
}

void arrayShuffle(int *array, size_t n) {
	if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

void arrayCopy(int *array, int *arrayNew, size_t n) {
	size_t i;
	for (i = 0; i < n; i++) {
		arrayNew[i] = array[i];
	}
}