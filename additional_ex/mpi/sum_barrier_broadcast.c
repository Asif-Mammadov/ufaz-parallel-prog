#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#define n 1000
int main(int argc, char *argv[])
{
	int rank, nprocs, s, s0 = 0, s1 = 0;
	MPI_Request request;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		for (int i = 0; i < n / 2; i++)
			s0 += i;
	}
	else if (rank == 1)
	{
		for (int i = n / 2; i < n; i++)
			s1 += i;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	printf("Hello, world.  I am procees %d s0=%d s1=%d\n", rank, s0, s1);
	fflush(stdout);

	MPI_Bcast(&s0, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
	MPI_Bcast(&s1, 1, MPI_INTEGER, 1, MPI_COMM_WORLD);

	if (rank == 1)
		printf("Sum = %d\n", s0 + s1);
	MPI_Finalize();
	return 0;
}