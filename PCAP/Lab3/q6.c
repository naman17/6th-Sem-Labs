#include <mpi.h>
#include <stdio.h>
#include <string.h>

void modifyArray(int array[], int size){
	for (int i = 0; i < size; ++i)
		if (i == 0)
			array[i] = array[i];
		else
			array[i] += array[i-1];
}

int main(int argc, char *argv[])
{
	int rank, size;
	int N, M, S, A[20], B[20];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		N = size;
		printf("Enter the size of the array: \n");
		scanf("%d", &M);
		printf("Enter the values: \n");
		for (int i = 0; i < M; ++i)
			scanf("%d", &A[i]);	
		S = M/N;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&S, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(A, S, MPI_INT, &B, S, MPI_INT, 0, MPI_COMM_WORLD);

	modifyArray(B, S);

	MPI_Gather(&B, S, MPI_INT, A, S, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0){
		for (int i = 0; i < M; ++i)
		{
			printf("%d   ", A[i]);
		}
	}

	MPI_Finalize();
	return 0;
}
