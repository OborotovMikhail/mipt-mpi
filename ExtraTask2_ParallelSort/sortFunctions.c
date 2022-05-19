#include <stdio.h>
#include <stdlib.h>

#include"sortFunctions.h"

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void bitonicSeqMerge(int *array, int start, int BseqSize, int direction) {
	if (BseqSize > 1) {
		int k = BseqSize / 2;
		for (int i = start; i < start + k; i++) {
			if (direction == (array[i] > array[i+k])) {
				swap(&array[i], &array[i+k]);
			}
		}
		
		bitonicSeqMerge(array, start, k, direction);
		bitonicSeqMerge(array, start+k, k, direction);
	}
}

void bitonicSeqSort(int *array, int start, int length, int direction) {
	if (length > 1) {
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
    	bitonicSeqSort(array, start, halfLen, 1);
    	bitonicSeqSort(array, start + halfLen, halfLen, 0);
    	bitonicSeqMerge(array, start, length, direction);
	}

    
}

void sortSequential(int *array, int length, int direction) {
	bitonicSeqSort(array, 0, length, direction);
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