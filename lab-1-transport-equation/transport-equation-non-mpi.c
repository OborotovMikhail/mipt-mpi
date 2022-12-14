/*Develop a sequential program that numerically solves
the transfer equation according to the difference scheme in accordance with the individual variant*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculateMethods.h"
#include "conditions.h"

int main(int argc, char **argv) {
  float X = 0, T = 0; // Coordinate x, and time t limits
  int K = 0, M = 0; // Data massive dimentions

  // Opening parameters file and reading parameters
  FILE *fileParameters = fopen("parameters.txt", "r");
  if (fileParameters == NULL) {
    printf("Failed to open parameters file\n");
    return (1);
  } else {
    fscanf(fileParameters, "%f %f %d %d", &X, &T, &K, &M);
    fclose(fileParameters);
  }

  float tau = T / K, h = X / M;
  
  float* data = (float*) malloc((K + 1) * (M + 1) * sizeof(float)); // Allocating memory for data structure



  free(data); // Releasing allocated memory

  return 0;
}