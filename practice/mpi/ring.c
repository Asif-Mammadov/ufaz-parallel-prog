#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv) {
  int next, prev, rank, size, value, sum = 0;
  MPI_Init(&argc, &argv);
  MPI_Request request;
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  next = (rank + 1) % size;
  prev = ((rank - 1) < 0) ? size + (rank - 1) : rank-1; 
  value = rank;
  do {
    MPI_Isend(&value, 1, MPI_INT, next, 100, MPI_COMM_WORLD, &request);
    MPI_Irecv(&value, 1, MPI_INT, prev, 100, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
    sum += value;
  } while (value != rank);
  printf("sum = %d\n", sum);

  MPI_Finalize();
  return 0;
}