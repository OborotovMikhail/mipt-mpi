#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <omp.h>

#include "arrayFunctions.h"
#include "sortFunctions.h"
#include "argStruct.h"

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
	int* array = (int*) malloc(arraySize * sizeof(int));
	arrayInit(array, arraySize);
	arrayShuffle(array, arraySize);

	// Creating an array for the sequential sort
	int* arraySequential = (int*) malloc(arraySize * sizeof(int));
	//arrayCopy(array, arraySequential, arraySize);
	arrayInit(arraySequential, arraySize);
	arrayShuffle(arraySequential, arraySize);

	// Thread variables
	pthread_t threads[threadsNum]; // Thread id array
	int status; // Status variable

	/* --------------- CONCURRENT SORT --------------- */

	// Creating and initializing thread arguments structure
  	threadArgs arguments[threadsNum];
  	for (int i = 0; i < threadsNum; i++) {
		arguments[i].id = i; // Tread id
		arguments[i].array = array; // Array pointer
  	}

  	// Starting time
	struct timespec timeStart, timeEnd; // Starting and ending time points
	double timeElapsed; // Elapsed time variable
	clock_gettime(CLOCK_MONOTONIC, &timeStart); // Getting start time

  	int i, j, direction, id;

    //numThreads =  omp_get_max_threads();

  	// the size of sub part
    int subSection = arraySize / threadsNum;

    arrayPrint(array, arraySize); // DEBUG

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
            bitonicSeq(j, i, array, direction);
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
            bitonicSeq(j * subSection, subSection, array, direction);
        }
    }

    // End time
	clock_gettime(CLOCK_MONOTONIC, &timeEnd); // Getting End time
	timeElapsed = timeEnd.tv_sec - timeStart.tv_sec; // Converting time
	timeElapsed += (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000000.0; // Converting time

    arrayPrint(array, arraySize); // DEBUG

	/* --------------- SEQUENTIAL SORT --------------- */

	arrayPrint(arraySequential, arraySize); // DEBUG

	// Starting time
	struct timespec timeStartSeq, timeEndSeq; // Starting and ending time points
	double timeElapsedSeq; // Elapsed time variable
	clock_gettime(CLOCK_MONOTONIC, &timeStartSeq); // Getting start time

	// Sorting sequentially
	sortSequential(arraySequential, arraySize);

	// End time
	clock_gettime(CLOCK_MONOTONIC, &timeEndSeq); // Getting End time
	timeElapsedSeq = timeEndSeq.tv_sec - timeStartSeq.tv_sec; // Converting time
	timeElapsedSeq += (timeEndSeq.tv_nsec - timeStartSeq.tv_nsec) / 1000000000.0; // Converting time

	arrayPrint(arraySequential, arraySize); // DEBUG

	/* --------------- PRINTING RESULTS --------------- */

	printf("Multi thread  - DONE - Time: %.10f sec\n", timeElapsed);
	printf("Single thread - DONE - Time: %.10f sec\n", timeElapsedSeq);

	// Releasing the memory
	free(array);
	free(arraySequential);

	return SUCCESS;
}