/*With the help of pthread, it is necessary to make a program that will calculate 
a definite integral of sin(1/x) function in the limit from a certain positive real 
number to some larger positive real number. It is necessary to balance the 
solution - the task execution time on all threads should be the same. 
So, the integration steps must be dynamic*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "function.h"
#include "integrate.h"
#include "argStruct.h"

#define SUCCESS 0
#define ERROR_OPEN_PARAMETERS 1
#define ERROR_CREATE_THREAD 2
#define ERROR_JOIN_THREAD 3

int main(int argc, char **argv) {
  float xMin, xMax; // Definite integral limits (set as a parameter)
  int stepsNum, threadsNum; // Total integration steps (set as a parameter)

  // Opening parameters file and reading parameters
  FILE *fileParameters = fopen("parameters.txt", "r");
  if (fileParameters == NULL) {
    printf("Failed to open parameters file\n");
    fclose(fileParameters);
    exit(ERROR_OPEN_PARAMETERS);
  } else {
    fscanf(fileParameters, "%f %f %d %d", &xMin, &xMax, &stepsNum, &threadsNum);
    fclose(fileParameters);
  }

  // Thread variables
  pthread_t threads[threadsNum]; // Thread id array
  int status, status_addr; // Status variables

  // Creating and initializing thread arguments structure
  threadArgs arguments[threadsNum];
  for (int i = 0; i < threadsNum; i++) {
    arguments[i].id = i; // Tread id
    arguments[i].func = &func; // Passing a pointer to function to be integrated
    arguments[i].xMin = xMin;
    arguments[i].xMax = xMax;
    arguments[i].stepsNum = stepsNum;
    arguments[i].integral = 0;
  }

  // Creating threads
  for (int i = 0; i < threadsNum; i++) {
    status = pthread_create(&threads[i], NULL, integrateThread, (void*) &arguments[i]);
    if (status != SUCCESS) {
      printf("Could not create thread with id %d\n", i);
      exit(ERROR_CREATE_THREAD);
    }
    printf("Successfully created thread %d\n", i); // Debug
  }

  // Joining threads
  for (int i = 0; i < threadsNum; i++) {
    status = pthread_join(threads[i], (void**)&status_addr);
    /*
    if (status != SUCCESS) {
      printf("Could not join thread with id %d, status = %d\n", i, status);
      exit(ERROR_JOIN_THREAD);
    }
    */
    printf("Successfully joined thread id %d, status_addr = %d\n", i, status_addr); // Debug
  }

  // Single-thread version
  double integral = integrate(func, xMin, xMax, stepsNum);
  printf("Integral: %lf\nNumber of steps (intervals): %d\n", integral, stepsNum);

  return 0;
}