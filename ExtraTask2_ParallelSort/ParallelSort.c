#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <omp.h>

#include "arrayFunctions.h"
#include "sortFunctions.h"

#define SUCCESS 10
#define ERROR_OPEN_PARAMETERS 11

#define UP 0
#define DOWN 1

int main(int argc, char **argv) {
	// Array size and the number of threads
	int arraySize, threadsNum;

	// Opening parameters file and reading parameters
	FILE *fileParameters = fopen("parameters.txt", "r");
	if (fileParameters == NULL) {
		printf("Failed to open parameters file\n");
		fclose(fileParameters);
		exit(ERROR_OPEN_PARAMETERS);
	} else {
		fscanf(fileParameters, "%d %d", &arraySize, &threadsNum);
		fclose(fileParameters);
	}

	// Creating an array
	int* array = (int*)malloc(arraySize * sizeof(int));
	if (array == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

	//printf("DEBUG: %d \n", (int) sizeof(array)); // DEBUG
	arrayInit(array, arraySize);
	arrayShuffle(array, arraySize);
	//printf("DEBUG: %ld \n", sizeof(array) / sizeof(int)); // DEBUG

	// Creating an array for the sequential sort
	int* arraySequential = (int*)malloc(arraySize * sizeof(int));
	if (arraySequential == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

	//arrayCopy(array, arraySequential, arraySize);
	arrayInit(arraySequential, arraySize);
	arrayShuffle(arraySequential, arraySize);

	/* --------------- SEQUENTIAL SORT --------------- */

	// Starting time
	struct timespec timeStartSeq, timeEndSeq; // Starting and ending time points
	double timeElapsedSeq; // Elapsed time variable
	clock_gettime(CLOCK_MONOTONIC, &timeStartSeq); // Getting start time

	// Sorting sequentially
	sortSequential(arraySequential, arraySize, 1);

	// End time
	clock_gettime(CLOCK_MONOTONIC, &timeEndSeq); // Getting End time
	timeElapsedSeq = (timeEndSeq.tv_sec - timeStartSeq.tv_sec) * 1000; // Converting time
	timeElapsedSeq += (timeEndSeq.tv_nsec - timeStartSeq.tv_nsec) / 1000000.0; // Converting time

	/* --------------- CONCURRENT SORT --------------- */

  	// Starting time
	struct timespec timeStart, timeEnd; // Starting and ending time points
	double timeElapsed; // Elapsed time variable
	clock_gettime(CLOCK_MONOTONIC, &timeStart); // Getting start time

  	int i, j, direction, id;
  	
    threadsNum =  4;

  	// the size of sub part
    int subSection = arraySize / threadsNum;

    // 1st
    for (i = 2; i <= subSection; i = 2 * i)
    {
#pragma omp parallel for shared(i, array) private(j, direction)
        for (j = 0; j < threadsNum; j += i)
        {
            if ((j / i) % 2 == 0)
                direction = UP;
            else
                direction = DOWN;
            bitonicSeqSort(array, j, i, direction);
        }
    }

    // 2nd
    for (i = 2; i <= threadsNum; i = 2 * i) {
        for (j = 0; j < threadsNum; j += i) {
            if ((j / i) % 2 == 0)
                direction = UP;
            else
                direction = DOWN;
            bitonicPar(j * subSection, i * subSection, array, direction, subSection);
        }
#pragma omp parallel for shared(j)
        for (j = 0; j < threadsNum; j++) {
            if (j < i)
                direction = UP;
            else
                direction = DOWN;
            bitonicSeqSort(array, j * subSection, subSection, direction);
        }
    }

    // End time
	clock_gettime(CLOCK_MONOTONIC, &timeEnd); // Getting End time
	timeElapsed = (timeEnd.tv_sec - timeStart.tv_sec) * 1000; // Converting time
	timeElapsed += (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000.0; // Converting time

	/* --------------- PRINTING RESULTS --------------- */

	arrayPrint(array, arraySize); // DEBUG

	printf("\nRESULTS:\n");
	
	printf("Single thread - ");
	if (arrayVerify(arraySequential, arraySize)) {
		printf("SORTED - ");
	} else {
		printf("UNSORTED - ");
	}
	printf("Time: %.10f ms\n", timeElapsedSeq);

	printf("Multi thread  - ");
	if (arrayVerify(array, arraySize)) {
		printf("SORTED - ");
	} else {
		printf("UNSORTED - ");
	}
	printf("Time: %.10f ms\n", timeElapsed);

	//arrayPrint(arraySequential, arraySize); // DEBUG

	// Releasing the memory
	free(array);
	free(arraySequential);

	return SUCCESS;
}