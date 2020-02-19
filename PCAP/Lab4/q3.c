#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank, size, countsum;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int mat[9], element;
	int mat2[3];
	if (rank == 0)
	{
		printf("Enter the elements of the matrix: \n");
		for (int i = 0; i < 9; ++i)
			scanf("%d", &mat[i]);
		printf("Enter the element to be searched\n");

		scanf("%d", &element);
	}
	MPI_Bcast(&element, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(mat, 3, MPI_INT, &mat2, 3, MPI_INT, 0, MPI_COMM_WORLD);

	int count = 0;
	for (int i = 0; i < 3; ++i)
		if (mat2[i] == element)
			count++;

	MPI_Reduce(&count, &countsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
		printf("The occurence of %d in matrix is: %d\n", element, countsum);

	MPI_Finalize();
	return 0;
}