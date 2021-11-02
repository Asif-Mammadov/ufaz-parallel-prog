#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#define n 10
int main(int argc, char *argv[])
{
	int rank, nprocs, sum[2], local_sum = 0;
	int block_length;
	MPI_Request request;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	block_length = 1;		
	if (rank == 0)
	{
		for (int i = 0; i < n / 2; i++)
			local_sum += i;
	}
	else if (rank == 1)
	{
		for (int i = n / 2; i < n; i++)
			local_sum += i;
	}
	MPI_Gather(&local_sum, 1, MPI_INTEGER, &sum, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

	if (rank == 0)
		printf("Sum = %d\n", sum[0] + sum[1]);
	MPI_Finalize();
	return 0;
}