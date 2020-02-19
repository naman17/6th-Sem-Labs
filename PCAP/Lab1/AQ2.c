#include <mpi.h>
#include <stdio.h>

int isPrime(int num){
	for (int i = 2; i < num; ++i)
		if (num % i == 0)
			return 0;
	return 1;
}

int main(int argc, char *argv[]){
	int rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(argc<=1) {
        printf("Enter a command line input");
        exit(1);
    }
    int num = atoi(argv[1]);
	if (rank == 0){
		printf("%d\n", num);
	}else{

	}
	MPI_Finalize();
	return 0;
}