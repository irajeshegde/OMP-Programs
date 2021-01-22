#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	int tag = 1, size, rank, source, dest, rc, count;
	char inmsg, outmsg = 'A';
	MPI_Init(&argc, &argv);
	MPI_Status stats;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0 && size > 2)
	{
		printf("\nOnly 2 tasks needed, ignoring extra\n");
		source = 1;
		dest = 1;
		rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
		rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &stats);
	}
	if (rank == 1)
	{
		source = 0;
		dest = 0;
		rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &stats);
		rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	}
	if (rank > 2)
		rc = MPI_Get_count(&stats, MPI_CHAR, &count);
	printf("\nTask %d is communicated containing %d from %d to %d\n", rank, inmsg, stats.MPI_SOURCE, stats.MPI_TAG);

	MPI_Finalize();
}