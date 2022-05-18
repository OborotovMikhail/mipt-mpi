#include <stdio.h>
#include <stdlib.h>

#include"arrayFunctions.h"

#define SUCCESS 0
#define ERROR_OPEN_PARAMETERS 1

int main(int argc, char **argv) {
  int arraySize, threadsNum; // Array size and the number of threads

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

  // Releasing the memory
  free(array);
  free(arraySequential);

  return 0;
}