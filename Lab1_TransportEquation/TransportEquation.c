/*Develop a parallel program using MPI technology that
numerically solves the transfer equation according to a difference scheme in accordance with
an individual variant*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculateMethods.h"
#include "conditions.h"

int main(int argc, char **argv) {
  int rank = 0, size = 0; // Rank of the process and world size

  MPI_Init(&argc, &argv); // Initializing MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Getting process rank
  MPI_Comm_size(MPI_COMM_WORLD, &size); // Getting world size

  MPI_Request request; // Request variable

  double runTime = MPI_Wtime(); // Running time

  float X = 0, T = 0; // Coordinate x, and time t limits
  int K = 0, M = 0; // Data massive dimentions

  // Opening parameters file and reading parameters
  FILE *fileParameters = fopen("parameters.txt", "r");
  if (fileParameters == NULL) {
    printf("Failed to open parameters file\n");
    fclose(fileParameters);
    return (1);
  } else {
    fscanf(fileParameters, "%f %f %d %d", &X, &T, &K, &M);
    fclose(fileParameters);
  }

  float tau = T / K, h = X / M; // Time and coordinate steps
  
  float* data = (float*) malloc((K + 1) * (M + 1) * sizeof(float)); // Allocating memory for data structure

  int m = 0, k = 0, n = M / 2; // Indexes

  conditionsInit(data, K, M, tau,h); // Initializing conditions

  // Calculating
  for (k = rank; k <= K; k += size) {
    int send = 0;
    int recv = 0;
    for (m = 1; m <= M; m++) {  
      if (rank == 0 && k == 0 && size > 1) {
        
        
        if (m == n * (send + 1)) {
          MPI_Isend((data + 1 + send * n),  n, MPI_FLOAT, (rank + 1) % size, k + 1, MPI_COMM_WORLD, &request);
          send++;
        }
      } else {
        
        if (m == 1 || m == n + 1) {
          MPI_Recv((data + (k-1)* (M + 1) + 1 + recv * n), n, MPI_FLOAT, (rank - 1 + size) % size, k, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          recv++;
        }
        calcRectangle(data, k, m, K, M, tau, h);
        if (m == n * (send + 1) && k <= K) {
          MPI_Isend((data + (k) * (M + 1) + 1 + send * n), n, MPI_FLOAT, (rank + 1) % size, k + 1, MPI_COMM_WORLD, &request);
          send++;
        }
        
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD); // Blocking until all processes are done

  // Sending all data to the process with rank 0
  if (rank == 0) {
    MPI_Status status;
    for (int i = 0; i <= K; i++) {
      if (i % size != 0) {
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Recv(data + status.MPI_TAG * (M + 1) + 1, M, MPI_FLOAT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
      }
      
    }
  } else {
    for (k = rank; k <= K; k += size) {
      MPI_Send((data + k * (M + 1) + 1), M, MPI_FLOAT, 0, k, MPI_COMM_WORLD);
    }
  }

  // Opening a file to store the result
  FILE *fileOutput = fopen("output.txt", "w+");
  if (fileOutput == NULL) {
    printf("Failed to open output file\n");
    fclose(fileOutput);
    return (1);
  }

  // Process with rank 0 is printing the result
  if(rank == 0){
    for(int k = 0;k <= K; k++) {
      for(int m = 0; m <= M; m++) {
        fprintf(fileOutput, "%.3g ", data[k * (M + 1) + m]);
        printf(" %.3f ", data[k * (M + 1) + m]);
      }
      printf("\n");
    }
  }

  fclose(fileOutput); // Closing output file

  free(data); // Releasing allocated memory 
  
  MPI_Finalize(); // Ending MPI

  return 0;
}