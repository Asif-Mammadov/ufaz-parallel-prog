#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include<stdlib.h>
#define N 100
int main(int argc, char **argv)
{
  int rank, nproc;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  int a[N];
  int block_size = (int)ceil(1.0 * N / nproc);
  int *chunk = (int*)malloc(N * sizeof(int));
  int s = 37;
  int index;
  if (rank == 0)
  {
    for (int i = 0; i < N; i++)
      a[i] = i;
  }
  MPI_Scatter(a, block_size, MPI_INTEGER, chunk, block_size, MPI_INTEGER, 0, MPI_COMM_WORLD);
  for (int i = 0; i < block_size; i++)
  {
    if (chunk[i] == s)
    {
      index = rank * block_size + i;
      printf("Index: %d\n", index);
      MPI_Abort(MPI_COMM_WORLD, 0);
    }
  }
  MPI_Finalize();
}