#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main(int argc, char *argv[])
{
	int rank, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		printf("Start process %d\n", rank);
		fflush(stdout);
		sleep(1);
		printf("End process %d\n", rank);
		fflush(stdout);
	}
	else if (rank == 1)
	{
		printf("Start process %d\n", rank);
		fflush(stdout);
		sleep(5);
		printf("End process %d\n", rank);
		fflush(stdout);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	printf("After Barrier I am %d of %d\n", rank, nprocs);
	fflush(stdout);
	MPI_Finalize();
	return 0;
}