#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "arrayFunctions.h"
#include "sortFunctions.h"
#include "argStruct.h"

#define SUCCESS 0
#define ERROR_OPEN_PARAMETERS 1

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
	arrayCopy(array, arraySequential, arraySize);

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

  	

	/* --------------- SEQUENTIAL SORT --------------- */

	arrayPrint(arraySequential, arraySize); // DEBUG

	// Starting time
	struct timespec timeStart, timeEnd; // Starting and ending time points
	double timeElapsed; // Elapsed time variable
	clock_gettime(CLOCK_MONOTONIC, &timeStart); // Getting start time

	// Sorting sequentially
	sortSequential(arraySequential, arraySize);

	// End time
	clock_gettime(CLOCK_MONOTONIC, &timeEnd); // Getting End time
	timeElapsed = timeEnd.tv_sec - timeStart.tv_sec; // Converting time
	timeElapsed += (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000000.0; // Converting time

	arrayPrint(arraySequential, arraySize); // DEBUG

	/* --------------- PRINTING RESULTS --------------- */

	printf("Single thread - DONE - Time: %.10f sec\n", timeElapsed);

	// Releasing the memory
	free(array);
	free(arraySequential);

	return 0;
}