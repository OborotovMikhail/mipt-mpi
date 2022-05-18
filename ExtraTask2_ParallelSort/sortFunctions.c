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

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void bitonicSeq(int start, int length, int *array, int direction) {
    int i, split_length;

    if (length == 1)
        return;

    if (length % 2 != 0 ) {
        printf("The length must be a power of 2\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
    for (i = start; i < start + split_length; i++) {
        if (direction == UP) {
            if (array[i] > array[i + split_length])
                swap(&array[i], &array[i + split_length]);
        }
        else {
            if (array[i] < array[i + split_length])
                swap(&array[i], &array[i + split_length]);
        }
    }

    bitonicSeq(start, split_length, array, direction);
    bitonicSeq(start + split_length, split_length, array, direction);
}

void bitonicPar(int start, int length, int *array, int direction, int subSection) {
	int i, split_length;

    if (length == 1)
        return;

    if (length % 2 != 0 ) {
        printf("The length must be a power of 2\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
#pragma omp parallel for shared(array, direction, start, split_length) private(i)
    for (i = start; i < start + split_length; i++) {
        if (direction == UP) {
            if (array[i] > array[i + split_length])
                swap(&array[i], &array[i + split_length]);
        }
        else {
            if (array[i] < array[i + split_length])
                swap(&array[i], &array[i + split_length]);
        }
    }

    if (split_length > subSection) {
        // subSection is the size of sub part-> n/numThreads
        bitonicPar(start, split_length, array, direction, subSection);
        bitonicPar(start + split_length, split_length, array, direction, subSection);
    }
}