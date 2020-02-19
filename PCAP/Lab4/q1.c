#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "ErrorHandler.h"

int main(int argc, char *argv[])
{
	int rank, size, fact=1, factsum, error_code;
	error_code = MPI_Init(&argc, &argv);ErrorHandler(error_code);
	error_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);ErrorHandler(error_code);
	error_code = MPI_Comm_size(MPI_COMM_WORLD, &size);ErrorHandler(error_code);

	for (int i = 1; i <= rank+1; ++i)
		fact *= i;

	error_code = MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);ErrorHandler(error_code);
	if (rank == size-1)
		printf("Sum of all the factorial = %d\n", factsum);

	MPI_Finalize();
	return 0;
}