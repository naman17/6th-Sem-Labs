#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size;
	
	int buffSize = 400;
	int buff[buffSize];
	
	int num;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	MPI_Buffer_attach(buff, buffSize);
	if (rank == 0)
	{
		for (int i = 1; i < size; ++i)
		{
			printf("\nEnter the number to send: \n");
			scanf("%d", &num);
			MPI_Bsend(&num, 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}
	}else{
		MPI_Recv(&num, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		fprintf(stdout, "I have recieved %d in process %d\n", num, rank);
		fflush(stdout);
		if (rank % 2 == 0)
			fprintf(stdout, "Rank: %d\t Received: %d\t Sqaure: %d\n", rank, num, num*num);
		else
			fprintf(stdout, "Rank: %d\t Received: %d\t Cube: %d\n", rank, num, num*num*num);
	}
	MPI_Buffer_detach(&buff, &buffSize);
	MPI_Finalize();
	return 0;
}