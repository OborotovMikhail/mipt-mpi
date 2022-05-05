/*With the help of pthread, it is necessary to make a program that will calculate 
a definite integral of sin(1/x) function in the limit from a certain positive real 
number to some larger positive real number. It is necessary to balance the 
solution - the task execution time on all threads should be the same. 
So, the integration steps must be dynamic*/

#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "integrate.h"

#define ERROR_OPEN_PARAMETERS 1

int main(int argc, char **argv) {
  float xMin, xMax; // Definite integral limits (set as a parameter)
  int stepsNum; // Total integration steps (set as a parameter)

  // Opening parameters file and reading parameters
  FILE *fileParameters = fopen("parameters.txt", "r");
  if (fileParameters == NULL) {
    printf("Failed to open parameters file\n");
    fclose(fileParameters);
    exit(ERROR_OPEN_PARAMETERS);
  } else {
    fscanf(fileParameters, "%f %f %d", &xMin, &xMax, &stepsNum);
    fclose(fileParameters);
  }

  double integral = integrate(func, xMin, xMax, stepsNum);

  printf("Integral: %lf\nNumber of steps (intervals): %d\n", integral, stepsNum);

  return 0;
}