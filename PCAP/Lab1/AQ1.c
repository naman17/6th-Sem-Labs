#include <mpi.h>
#include <stdio.h>

int isPrime(int num){
	for (int i = 2; i < num; ++i)
		if (num % i == 0)
			return 0;
	return 1;
}

int main(int argc, char *argv[]){
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0){
		printf("Using rank 0\n");
		for (int i = 2 ; i < 50; ++i)
			if (isPrime(i))
				printf("%d\t", i);
	}else{
		printf("Using rank 1\n");
		for (int i = 50; i < 100; ++i)
			if (isPrime(i))
				printf("%d\t", i);
	}
	MPI_Finalize();
	return 0;
}