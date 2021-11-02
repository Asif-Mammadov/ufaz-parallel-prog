#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <math.h>
#define N 7
int main(int argc, char *argv[])
{
	int rank, nprocs, arr[N], local_sum = 0, block_length, sums[4];
	
  for(int i = 0; i < N; i++){
    arr[i] = i;
  }

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	block_length = (int)ceil(N * 1.0/nprocs);
	
  for(int i = rank*block_length; i < rank*block_length+block_length; i++){
    printf("Process %d || element i is %d\n", rank, i);
    if(i >= N) break;
    local_sum += arr[i];
  }

	MPI_Gather(&local_sum, 1, MPI_INTEGER, sums, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

  int global_sum = 0;
	if(rank == 0){
    for(int i = 0; i < nprocs; i++){
      printf("sums[%d] is %d\n", i, sums[i]);
      global_sum += sums[i];
    }

    printf("Global sum is %d\n", global_sum);
  }

	MPI_Finalize();
	return 0;
}