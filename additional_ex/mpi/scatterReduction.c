#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#define N 10
int main(int argc, char **argv)
{
  int *data, *values, block_length, nprocess, rank, localsum = 0;
  int globalsum = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocess);
  block_length = (int)ceil(N * 1.0 / nprocess);
  data = (int *)malloc(block_length * sizeof(int));
  values = (int *)malloc(N * sizeof(int));

  int sum[nprocess]; // [0, 1, 2, 3]
  if (rank == 0)
  {
    // sum = (int *)malloc(nprocess * sizeof(int));
    printf("Init array by process %d\n", rank);
    for (int i = 0; i < N; i++)
      values[i] = i;
  }
  MPI_Scatter(values, block_length, MPI_INTEGER, data, block_length, MPI_INTEGER, 0, MPI_COMM_WORLD);
  localsum = 0;
  for (int i = 0; i < block_length; i++)
  {
    localsum += data[i];
  }
  printf("process %d || local sum is %d\n", rank, localsum);

  // MPI_Gather(&localsum, 1, MPI_INTEGER, &sum, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
  MPI_Reduce(&localsum, &globalsum, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0)
  {
    printf("Sum : %d\n", globalsum);
  }
  MPI_Finalize();
}