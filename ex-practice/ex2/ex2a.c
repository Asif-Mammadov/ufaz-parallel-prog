#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define N 100000
int main(int argc, char **argv)
{
  int rank, tag = 100;
  double start_time, end_time;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int a[N];
  int b[N]; 
  int *c = (int *)malloc(N * sizeof(int));
  if (rank == 0)
  {
    for (int i = 0; i < N; i++)
    {
      a[i] = i;
      b[i] = 2 * i;
    }
    start_time = MPI_Wtime(); 
    MPI_Send(a, N, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
    MPI_Send(b, N, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
    MPI_Recv(c, N, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    end_time = MPI_Wtime(); 
    // for (int i = 0; i < N; i++)
    // {
    //   printf("c[%d] = %d\n", i, c[i]);
    // }
    printf("Time: %lfs\n", end_time-start_time);
  }
  else if (rank == 1)
  {
    MPI_Recv(a, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(b, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    for (int i = 0; i < N; i++)
      c[i] = a[i] + b[i];
    MPI_Send(c, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
}