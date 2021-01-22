#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{

	int input, product = 1, res = 1, rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		printf("\nEnter the number to calculate factorial -> ");
		scanf("%d", &input);
	}
	MPI_Bcast(&input, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int first = (rank * input) / size + 1;
	int last = ((rank + 1) * input) / size;
	int i = 0;
	for (i = first; i <= last; i++)
	{
		product *= i;
	}

	MPI_Reduce(&product, &res, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	if (rank == 0)
		printf("\nResult - Factorial of %d is %d\n", input, res);
}
