#include <mpi.h>
#include <math.h>
#include <stdio.h>
int main(int argc, char  *argv[])
{
	int rank, size, done=0, n, rc;
	double pi2, pi, h, sum, x, a;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0)
	{
		printf("Enter the number of intervals\n");
		scanf("%d", &n);
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (n == 0)
		return 0;
	//parallel code
	h = 1.0 / (double) n;
	sum = 0.0;
	for (int i = rank+1; i <= n; i += size){
		x = h* ((double)i - 0.5);
		sum += 4.0 / (1.0 + x*x);
	}
	pi2 = h*sum;
	MPI_Reduce(&pi2, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		printf("approx value of pi is %f\n", pi);
	}

	MPI_Finalize();
	return 0;
}