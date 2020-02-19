#include <mpi.h>
#include <stdio.h>
#include <ctype.h>

int fact(int num){
	int f = 1;
	for (int i = 1; i <= num; ++i)
	{
		f = f*i;
	}

	return f;
}


int main(int argc, char *argv[])
{
	int rank, size;
	int N, A[10], B[10], c, f, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		
		N = size;
		printf("Enter %d values: \n", N);
		for (int i = 0; i < N; ++i)
			scanf("%d", &A[i]);
	}

	MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);
	f=fact(c);
	printf("I have received %d in process %d : factorial = %d\n", c, rank, f);
	MPI_Gather(&f, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		int sum = 0;
		printf("The sum of all the factorials in root is: ");
		for (int i = 0; i < N; ++i)
			sum += B[i];
			
		printf("%d\n", sum);
	}

	MPI_Finalize();
	return 0;
}