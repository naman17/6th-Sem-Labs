#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int a = 5;
	int b = 7;
	switch(rank){
		case 0: printf("Addition of %d, and %d is %d \n", a, b, a+b);
				break;
		case 1: printf("Subtraction of %d, and %d is %d \n", a, b, a-b);
				break;
		case 2: printf("Multiplication of %d, and %d is %d \n", a, b, a*b);
				break;
		case 3: printf("Division of %d, and %d is %d \n", a, b, a/b);
				break;
		default: break;

	}
	MPI_Finalize();
	return 0;
}
