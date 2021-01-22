#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	int size, rank, prev, next, tag1 = 1, tag2 = 2, buf_recv[2], buf_send[2];
	MPI_Request reqs[20];
	MPI_Status stats[2];
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	prev = rank - 1;
	next = rank + 1;
	buf_send[0] = 10;
	buf_send[1] = 20;
	if (rank == 0)
		prev = size - 1;
	if (rank == (size - 1))
		next = 0;
	MPI_Irecv(&buf_recv[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf_recv[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);
	MPI_Isend(&buf_send[0], 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&buf_send[1], 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);

	MPI_Waitall(4, reqs, stats);
	printf("\nTasks %d communicated with tasks %d and %d", rank, prev, next);
	MPI_Finalize();
	return 0;
}
