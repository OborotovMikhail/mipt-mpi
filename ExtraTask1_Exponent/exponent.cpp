#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	if (argc < 1) {
		printf("Invalid argument");
		return -1;
	}

	int N = atoi(argv[1]);
	
	int size, rank;

	if (N > 1) {
		MPI_Init(&argc, &argv);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
		double start_time = MPI_Wtime();
		double value = 0;

		int i = 0;

		int start = rank * N / size + 1;
		int finish = (rank + 1) * N / size;
			
		for (i = start; i <= finish; i++) {
			value += 1.0 / i / i;
		}

		if (rank == 0) {

			double add_value = 0;
			int recv_rank = 1;

			for (;recv_rank < size; recv_rank++) {
				MPI_Recv(&add_value, 1, MPI_DOUBLE, recv_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				value += add_value;
			}

 			double end_time = MPI_Wtime();
			double time = (end_time - start_time) * 1000;

			printf("The result %lg, time required %lg ms\n", value, time);

		} else {
			MPI_Send(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}

		MPI_Finalize();
	}

	return 0;
}