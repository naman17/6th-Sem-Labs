#include <mpi.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	int rank, size;
	int N, M, A[20], B[10], c, f, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		N = size;
		printf("Enter the value of M: ");
		scanf("%d", &M);
		printf("Enter the values: \n");
		for (int i = 0; i < N*M; ++i)
				scanf("%d", &A[i]);		
	}
	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(A, M, MPI_INT, &B, M, MPI_INT, 0, MPI_COMM_WORLD);

	int sum = 0;
	int avg=0;
	for (int i = 0; i < M; ++i)
	{
		sum += B[i];
		printf("I have received %d in rank %d\n", B[i], rank);
	}
	avg = sum/M;

	MPI_Gather(&avg, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		sum = 0;
		avg = 0;
		for (int i = 0; i < N; ++i){
			printf("The value received in root is : %d\n", B[i]);
			sum += B[i];
		}
		avg = sum/M;
		printf("The avg calculated in root is %d\n", avg);
			
	}

	MPI_Finalize();
	return 0;
}


// int main(int argc, char *argv[])
// {
// 	int rank, size;
// 	int N, M, A[10], B[10], c, f, i;
// 	MPI_Init(&argc, &argv);
// 	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
// 	MPI_Comm_size(MPI_COMM_WORLD, &size);

// 	if (rank == 0)
// 	{
// 		N = size;
// 		printf("Enter the value of M: ");
// 		scanf("%d", &M);
// 		printf("Enter the values: \n");
// 		for (int i = 0; i < N; ++i)
// 			for (int j = 0; j < M; ++j)
// 				scanf("%d", &MAT[i][j]);
// 	}
// 	MPI_Barrier(MPI_COMM_WORLD);

// 	MPI_Scatter(MAT, M, MPI_INT, &A, M, MPI_INT, 0, MPI_COMM_WORLD);

// 	for (int i = 0; i < M; ++i)
// 	{
// 		printf("I have received %d in rank %d\n", A[i], rank);
// 		// printf("%d\n", A[i]);
// 	}
	
	// MPI_Gather(&f, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// if (rank == 0)
	// {
	// 	int sum = 0;
	// 	printf("The sum of all the factorials in root is: ");
	// 	for (int i = 0; i < N; ++i)
	// 		sum += B[i];
			
	// 	printf("%d\n", sum);
	// }

// 	MPI_Finalize();
// 	return 0;
// }