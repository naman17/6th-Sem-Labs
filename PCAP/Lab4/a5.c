#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>


int main(int argc, char *argv[]){
	int size, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;

	int matrix[25];
	int matArray[5];
	int maxArray[5];
	int minArray[5];

	int sum = 0;
	int finalSum = 0;

	if(rank == 0){
		printf("Enter 25 elements of a matrix: \n");
		for (int i = 0; i < 25; ++i)
			scanf("%d", &matrix[i]);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(matrix, 5, MPI_INT, matArray, 5, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Hello\n");

	MPI_Reduce(&matArray, &maxArray, 5, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Bcast(&maxArray, 5, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Reduce(&matArray, &minArray, 5, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Bcast(&minArray, 5, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < 5; ++i)
		if(i == rank){
			matArray[i] = 0;
		}else if(i > rank){
			matArray[i] = minArray[rank];
		}else{
			matArray[i] = maxArray[rank];
		}

	MPI_Gather(&matArray, 5, MPI_INT, matrix, 5, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0){
		for (int i = 0; i < 25; ++i)
		{
			if(i % 5 == 0){
				printf("\n");
			}
			printf("%d\t", matrix[i]);
		}
	}

	printf("\n");

	MPI_Finalize();
	return 0;
}