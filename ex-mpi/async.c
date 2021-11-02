#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {
  int rank;
  MPI_Request request;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int n = 100, tag=200;
  int value[n];
  if (rank == 0) {
    for (int i = 0; i < n; i++)
      value[i] = i;
      // MPI_Send(value, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
      MPI_Issend(&value, n, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, &request);
  } else if (rank == 1) {
      MPI_Irecv(&value, n, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, &request);
  }
  MPI_Finalize();
  return 0;
}