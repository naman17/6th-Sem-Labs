#include <mpi.h>
#include <stdio.h>
#include <string.h>

int count(char str[]){
	int c = 0;
	for (int i = 0; i < strlen(str); ++i)
		if (strchr("aeiouAEIOU", str[i]) == NULL)
			c++;

	return c;
}


int main(int argc, char *argv[])
{
	int rank, size;
	char str[100], str2[100];
	int N, M, A[20], c;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		N = size;
		printf("Enter the string: \n");
		gets(str);	
		M = strlen(str)/N;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(str, M, MPI_CHAR, &str2, M, MPI_CHAR, 0, MPI_COMM_WORLD);

	c = count(str2);
	printf("Rank: %d, String: %s, Non-Vowel Count: %d\n", rank, str2, c);
	MPI_Gather(&c, 1, MPI_INT, A, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		int sum = 0;
		for (int i = 0; i < N; ++i){
			printf("The value received in root is : %d\n", A[i]);
			sum += A[i];
		}
		printf("Total number of non vowels are: %d\n", sum);
			
	}

	MPI_Finalize();
	return 0;
}
