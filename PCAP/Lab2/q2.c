#include <mpi.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int rank, size;
	int num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (rank == 0)
	{
		for (int i = 1; i < size; ++i)
		{
			printf("\nEnter the number to send: \n");
			scanf("%d", &num);
			MPI_Send(&num, 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}
	}else{
		MPI_Recv(&num, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		fprintf(stdout, "I have recieved %d in process %d\n", num, rank);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}