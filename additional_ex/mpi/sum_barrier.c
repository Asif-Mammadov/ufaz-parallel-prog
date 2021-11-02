#include<stdio.h>
#include<mpi.h>

#define N 10000
int main(int argc, char *argv[]) {
  int rank, code, tag = 100;
  int tmp, sum=0;
  int a[N];
  for (int i = 0; i < N; i++)
    a[i] = i * i % 99;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */

  if (rank == 0) {
    for (int i = 0; i < N/2; i++)
      sum += a[i];
  } else if (rank == 1) {
    for (int i = N/2; i < N; i++)
      sum += a[i];
  }
  MPI_Barrier(MPI_COMM_WORLD);

  if (rank == 0) {
    MPI_Recv(&tmp, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
    printf("Sum = %d\n", sum + tmp);
  } else if (rank == 1) {
    MPI_Send(&sum, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD); }

  MPI_Finalize();
  return 0;
}