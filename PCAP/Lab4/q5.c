#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "ErrorHandler.h"

int main(int argc, char *argv[])
{
	int rank, size, countsum, error_code;
	error_code = MPI_Init(&argc, &argv);
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	error_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	ErrorHandler(error_code);
	error_code = MPI_Comm_size(MPI_COMM_WORLD, &size);
	ErrorHandler(error_code);
	int mat[16], element;
	int mat2[4], mat3[4];
	if (rank == 0)
	{
		printf("Enter the elements of the 4x4 matrix: \n");
		for (int i = 0; i < 16; ++i)
			scanf("%d", &mat[i]);
	}
	error_code = MPI_Bcast(&element, 1, MPI_INT, 0, MPI_COMM_WORLD);
	ErrorHandler(error_code);
	error_code = MPI_Scatter(mat, 4, MPI_INT, &mat2, 4, MPI_INT, 0, MPI_COMM_WORLD);
	ErrorHandler(error_code);
	error_code = MPI_Scan(&mat2, &mat3, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	ErrorHandler(error_code); 
	for (int i = 0; i < 4; ++i)
		printf("%d  ", mat3[i]);
	printf("\n");
	MPI_Finalize();
	return 0;
}