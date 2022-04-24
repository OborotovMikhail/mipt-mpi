#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*Write a program that measures the message transmission delay between
two network nodes using MPI technology*/

int main(int argc, char **argv) {
  int rank = 0, size = 0; // Rank of the process and world size
  double time = 0; // Time variable

  MPI_Init(&argc, &argv); // Initializing MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Getting process rank
  MPI_Comm_size(MPI_COMM_WORLD, &size); // Getting world size

  // In case there is less than 2 processes
  if (size < 2) {
    printf("Please enter 2 or more processes\n");
    MPI_Finalize();
    return 0;
  }

  // If process rank 0
  if (rank == 0) {
    time = MPI_Wtime(); // Getting time
    MPI_Send(&time, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD); // Sending time to process rank 1
    printf("My rank is %d, my time is %lg ms, sending time to process 1\n", rank, time * 1000);
  }

  // If process rank 1
  if (rank == 1) {
    printf("My rank is %d, my time is %lg ms, recieving time from process 0\n", rank, MPI_Wtime() * 1000);
    MPI_Recv(&time, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Recieving time from process rank 0
    printf("My rank is %d, time difference is %lg ms\n", rank, (time - MPI_Wtime()) * 1000);
  }

  MPI_Finalize(); // Ending MPI
  
  return 0;
}