#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

/*
PCAP EXAM
PCCAAAPPPP     EEEEEEXXXXXXXAAAAAAAAMMMMMMMMM

N - 3
*/


int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	char inputString[100];
	char recvString[100];
	char tempString[100];
	char outputString[200];
	int tempLengths[10];

	int length = 0;
	int m = 0;

	if (rank == 0){
		printf("Enter the input string: \n");
		gets(inputString);
		length = strlen(inputString);
		m = length/size;
	}

	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(inputString, m, MPI_CHAR, &recvString, m, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	recvString[m] = '\0';

	int index = 0;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < rank*m+i+1; ++j)
			tempString[index++] = recvString[i];

	printf("RANK %d | %s\n", rank, tempString);
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Gather(&index, 1, MPI_INT, tempLengths, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Send(tempString, index, MPI_CHAR, 0, 1, MPI_COMM_WORLD);

	if(rank == 0){
		for(int i = 0; i < size; i++){
			char temp[100];
			MPI_Recv(temp, tempLengths[i], MPI_CHAR, i, 1, MPI_COMM_WORLD, &status);
			temp[tempLengths[i]] = '\0';
			if(i == 0)
				strcpy(outputString, temp);
			else
				strcat(outputString, temp);
		}

		printf("\nFinal String:\nRANK %d | %s\n", rank, outputString);
	}

	MPI_Finalize();
	return 0;

}
