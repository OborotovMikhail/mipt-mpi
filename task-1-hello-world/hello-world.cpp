#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  printf("Before MPI_INIT\n");

  int rank, size;

  // Start of parallel part
  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &size); // Getting total number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Getting rank of this process

  printf("Hello World!\nMy rank: %d, Total number of processes: %d\n", rank, size);

  // End 
  MPI_Finalize();

  printf("After MPI_Finalize\n");
  
  return 0;
}