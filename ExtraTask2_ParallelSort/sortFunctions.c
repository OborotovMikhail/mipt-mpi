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

void bitonicSeqMerge(int start, int BseqSize, int *array, int direction) {
	if (BseqSize > 1){
		int k = BseqSize / 2;
		for (int i = start; i < start + k; i++) {
			if (direction == (array[i] > array[i+k])) {
				//swap(&array[i], &array[i+k]);
				int t = array[i];
				array[i] = array[i+k];
				array[i+k] = t;
			}
		}
		
		bitonicSeqMerge(start, k, array, direction);
		bitonicSeqMerge(start+k, k, array, direction);
	}
}

void bitonicSeq(int start, int length, int *array, int direction) {
	if (length > 1) {
		if (length % 2 != 0 ) {
        	printf("The length must be a power of 2\n");
        	exit(13);
    	}

    	int halfLen = length / 2;
    	/*
    	// bitonic split
    	int i;
    	for (i = start; i < start + halfLen; i++) {
    	    if (direction == UP) {
            if (array[i] > array[i + halfLen])
                swap(&array[i], &array[i + halfLen]);
        	}
        	else {
        	    if (array[i] < array[i + halfLen])
                swap(&array[i], &array[i + halfLen]);
        	}
        	arrayPrint(array, length); // DEBUG
    	}
		*/
    	bitonicSeq(start, halfLen, array, 1);
    	bitonicSeq(start + halfLen, halfLen, array, 0);
    	bitonicSeqMerge(start, halfLen, array, direction);
	}

    
}

void sort(int *array, int length, int direction) {
	bitonicSeq(0, length, array, direction);
}

void bitonicPar(int start, int length, int *array, int direction, int subSection) {
	int i, halfLen;

    if (length == 1)
        return;

    if (length % 2 != 0 ) {
        printf("The length must be a power of 2\n");
        exit(0);
    }

    halfLen = length / 2;

    // bitonic split
#pragma omp parallel for shared(array, direction, start, halfLen) private(i)
    for (i = start; i < start + halfLen; i++) {
        if (direction == UP) {
            if (array[i] > array[i + halfLen])
                swap(&array[i], &array[i + halfLen]);
        }
        else {
            if (array[i] < array[i + halfLen])
                swap(&array[i], &array[i + halfLen]);
        }
    }

    if (halfLen > subSection) {
        // subSection is the size of sub part-> n/numThreads
        bitonicPar(start, halfLen, array, direction, subSection);
        bitonicPar(start + halfLen, halfLen, array, direction, subSection);
    }
}