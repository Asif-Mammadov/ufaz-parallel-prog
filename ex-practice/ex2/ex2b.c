#include <stdio.h>
#include <mpi.h>
#include<math.h>
#include <stdlib.h>
#define N 100000:q


int main(int argc, char **argv)
{
  int rank, tag = 100, nproc;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  int a[N];
  int b[N];
  int c[N]; 
  int block_size = (int) ceil(1.0 * N/nproc);
  int a_chunk[block_size];
  int b_chunk[block_size];
  int c_chunk[block_size];
  double start_time, end_time;
  if (rank == 0)
  {
    for (int i = 0; i < N; i++)
    {
      a[i] = i;
      b[i] = 2 * i;
    }
    start_time = MPI_Wtime();
  }
  MPI_Scatter(a, block_size, MPI_INTEGER, a_chunk, block_size, MPI_INTEGER, 0, MPI_COMM_WORLD);
  MPI_Scatter(b, block_size, MPI_INTEGER, b_chunk, block_size, MPI_INTEGER, 0, MPI_COMM_WORLD);
  for (int i = 0; i<block_size; i++)
    c_chunk[i] = a_chunk[i] + b_chunk[i];
  MPI_Gather(c_chunk, block_size, MPI_INTEGER, c, block_size, MPI_INTEGER, 0, MPI_COMM_WORLD);
  if (rank == 0){
    end_time = MPI_Wtime();
    printf("Time : %lf\n", end_time - start_time);
    // for (int i = 0; i < N; i++) {
    //   printf("%d %d %d\n", a[i], b[i], c[i]);
    // }
  }
  // else if (rank == 1)
  // {
  //   MPI_Recv(a, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  //   MPI_Recv(b, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  //   for (int i = 0; i < N; i++)
  //     c[i] = a[i] + b[i];
  //   MPI_Send(c, N, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
  // }
  MPI_Finalize();
}