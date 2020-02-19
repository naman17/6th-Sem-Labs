#include <mpi.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int rank, size;
	char word[10];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (rank == 0)
	{
		printf("Enter the word to send: \n");
		scanf("%s", word);
		MPI_Ssend(word, 10, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		fprintf(stdout, "I have send %s to process 1\n", word);
		fflush(stdout);
		MPI_Recv(word, 10, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
		fprintf(stdout, "I have recieved %s from process 1\n", word);
		fflush(stdout);
	}else{
		MPI_Recv(word, 10, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
		// fprintf(stdout, "I have recieved %s in process 1\n", word);
		fflush(stdout);
		int i = 0;
		while(word[i] != '\0'){
			if (isupper(word[i]))
				word[i] = tolower(word[i]);
			else
				word[i] = toupper(word[i]);
			i++;
		}
		MPI_Ssend(word, 10, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}