#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include"sortFunctions.h"

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
    printf("swap\n");
}

void bitonicSeqMerge(int *array, int start, int length, int direction) {
	if (length > 1) {
		int halfLen = length / 2;
		for (int i = start; i < start + halfLen; i++) {
			if (direction == (array[i] > array[i+halfLen])) {
				swap(&array[i], &array[i+halfLen]);
			}
		}
		
		bitonicSeqMerge(array, start, halfLen, direction);
		bitonicSeqMerge(array, start + halfLen, halfLen, direction);
	}
}

void bitonicSeqSort(int *array, int start, int length, int direction) {
	if (length > 1) {
		int halfLen = length / 2;

    	bitonicSeqSort(array, start, halfLen, 1);
    	bitonicSeqSort(array, start + halfLen, halfLen, 0);
    	bitonicSeqMerge(array, start, length, direction);
	}
}

void sortSequential(int *array, int length, int direction) {
	bitonicSeqSort(array, 0, length, direction);
}

typedef struct threadArgs {
	int id; // Thread id
	int* array;
	int start;
	int length;
	int direction;
	int subSection;
} threadArgs;

void sortParallel(int *array, int length, int direction, int subSection) {
	threadArgs arguments;
	
    arguments.id = -1;
    arguments.array = array;
    arguments.start = 0;
    arguments.length = length;
    arguments.direction = direction;
    arguments.subSection = subSection;

	bitonicParSort((void*) &arguments);
}

void* bitonicParSort(void *input) {
	threadArgs *args = (threadArgs*) input; // Changing argument structure type

	if (args->length > 1) {
		int halfLen = args->length / 2;
		printf("len = %d\n", args->length);
		if (halfLen >= args->subSection) {
			pthread_t threads[2]; // Thread id array
			//printf("hi\n");
			//printf("%d %d\n", halfLen, args->subSection);

			// Splitting into 2 threads
			threadArgs arguments[2];
			for (int i = 0; i < 2; i++) {
    			arguments[i].id = i; // Tread id
    			arguments[i].array = args->array;
    			arguments[i].start = args->start;
    			arguments[i].length = halfLen;
    			arguments[i].subSection = args->subSection;
  			}

  			// Creating threads
  			arguments[0].direction = 1;
  			int status = pthread_create(&threads[0], NULL, bitonicParSort, (void*) &arguments[0]);
  			arguments[1].direction = 0;
  			arguments[1].start += halfLen;
  			status = pthread_create(&threads[1], NULL, bitonicParSort, (void*) &arguments[1]);

  			// Joining threads
  			for (int i = 0; i < 2; i++) {
  				void *returnValue;
  				status = pthread_join(threads[i], &returnValue);
  			}
		} else {
			bitonicSeqSort(args->array, args->start, halfLen, 1);
    		bitonicSeqSort(args->array, args->start + halfLen, halfLen, 0); // MB PROBLEM
		}

    	bitonicSeqMerge(args->array, args->start, args->length, args->direction);
	}
}

void bitonicPar(int start, int length, int *array, int direction, int subSection) {
	int i, halfLen;

    if (length == 1)
        return;

    halfLen = length / 2;

	
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
        bitonicPar(start, halfLen, array, direction, subSection);
        bitonicPar(start + halfLen, halfLen, array, direction, subSection);
    }
}