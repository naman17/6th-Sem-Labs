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
		printf("\nEnter the number to send: \n");
		scanf("%d", &num);

		MPI_Send(&num, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&num, 1, MPI_INT, size-1, size, MPI_COMM_WORLD, &status);
		printf("The number is %d\n", num);
	}else{
		MPI_Recv(&num, 1, MPI_INT, rank-1, rank, MPI_COMM_WORLD, &status);
		printf("I have recieved %d in process %d\n", num, rank);
		num++;
		MPI_Send(&num, 1, MPI_INT, (rank+1) % size, rank+1, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}