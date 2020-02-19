#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int rank, size;
	char str[100], str2[100], str3[100], str4[100];
	int N, S1, S2, A[20], c;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)
	{
		N = size;
		printf("Enter the string 1: \n");
		gets(str);
		printf("Enter the string 2: \n");
		gets(str2);		
		S1 = strlen(str)/N;
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&S1, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(str, S1, MPI_CHAR, &str3, S1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Scatter(str2, S1, MPI_CHAR, &str4, S1, MPI_CHAR, 0, MPI_COMM_WORLD);

	strcat(str3,str4);
	MPI_Gather(&str3, S1*2, MPI_CHAR, str4, S1*2, MPI_CHAR, 0, MPI_COMM_WORLD);

	if (rank == 0)
		puts(str4);

	MPI_Finalize();
	return 0;
}
