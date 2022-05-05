/*With the help of pthread, it is necessary to make a program that will calculate 
a definite integral of sin(1/x) function in the limit from a certain positive real 
number to some larger positive real number. It is necessary to balance the 
solution - the task execution time on all threads should be the same. 
So, the integration steps must be dynamic*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "function.h"
#include "integrate.h"
#include "argStruct.h"

#define SUCCESS 0
#define ERROR_OPEN_PARAMETERS 1

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
  int status; // Status variable

  // Creating and initializing thread arguments structure
  // Also distributing the intervals between threads
  threadArgs arguments[threadsNum]; // Creating thread argument structure
  int stepsPerThread = stepsNum / threadsNum; // Number of steps per 1 thread
  double xStep = (xMax - xMin) / stepsNum; // X step
  for (int i = 0; i < threadsNum; i++) {
    arguments[i].id = i; // Tread id
    arguments[i].func = &func; // Passing a pointer to function to be integrated
    arguments[i].xMin = xMin + xStep * i * stepsPerThread; // Lower limit for 1 thread
    arguments[i].xMax = xMin + xStep * ((i + 1) * stepsPerThread); // Upper limit for 1 thread
    arguments[i].stepsNum = stepsPerThread;
    arguments[i].integral = 0;
  }

  // Creating threads
  printf("Creating threads\n");
  for (int i = 0; i < threadsNum; i++) {
    printf("Thread %d - ", i);

    status = pthread_create(&threads[i], NULL, integrateThread, (void*) &arguments[i]);

    // Checking pthread create status
    switch (status) {
      case SUCCESS:
        printf("The thread created successfully\n");
        break;
      case EAGAIN:
        printf("Insufficient resources to create another thread\n");
        break;
      case EINVAL:
        printf("Invalid settings in attr\n");
        break;
      case EPERM:
        printf("No permission to set the scheduling policy and parameters specified in attr\n");
        break;
      default:
        printf("Error occurred when creating the thread\n");
    }
  }
  printf("\n");

  // Joining threads
  printf("Joining threads\n");
  for (int i = 0; i < threadsNum; i++) {
    printf("Thread %d - ", i);

    void *returnValue;
    status = pthread_join(threads[i], &returnValue);

    // Checking value returned by the thread
    if (returnValue == PTHREAD_CANCELED)
      printf("The thread was canceled - ");
    else
      printf("Returned value %d - ", (int)returnValue);

    // Checking pthread join status
    switch (status) {
      case SUCCESS:
        printf("The thread joined successfully\n");
        break;
      case EDEADLK:
        printf("Deadlock detected\n");
        break;
      case EINVAL:
        printf("The thread is not joinable\n");
        break;
      case ESRCH:
        printf("No thread with given ID is found\n");
        break;
      default:
        printf("Error occurred when joining the thread\n");
    }
  }
  printf("\n");

  // Printing results (integrals) from the threads
  printf("Multi-thread results\n");
  for (int i = 0; i < threadsNum; i++) {
    printf("Thread %d - ", arguments[i].id);
    printf("Integral: %.15f - ", arguments[i].integral);
    printf("Time: %.10f sec\n", (double)arguments[i].time);
  }
  printf("\n");

  // Calculating result integral (sum of all threads)
  double resultIntegral = 0;
  for (int i = 0; i < threadsNum; i++) {
    resultIntegral += arguments[i].integral;
  }
  printf("Resulting integral: %.15f\n", resultIntegral);
  printf("\n");

  // Single-thread version
  struct timespec timeStart, timeEnd; // Starting and ending time points
  double timeElapsed; // Elapsed time variable
  clock_gettime(CLOCK_MONOTONIC, &timeStart); // Getting start time
  double integral = integrate(func, xMin, xMax, stepsNum); // Single-thread integral calculation
  clock_gettime(CLOCK_MONOTONIC, &timeEnd); // Getting End time
  timeElapsed = timeEnd.tv_sec - timeStart.tv_sec; // Converting time
  timeElapsed += (timeEnd.tv_nsec - timeStart.tv_nsec) / 1000000000.0; // Converting time

  printf("Single thread - Integral: %.15f - ", integral);
  printf("Time: %.10f sec\n", timeElapsed);

  return 0;
}