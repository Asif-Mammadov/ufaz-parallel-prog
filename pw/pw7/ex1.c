#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv) {
  int rank, rank_value, sum = 0, dest_rank, src_rank, size, tag = 200, code;
  MPI_Request request;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  dest_rank = (rank + 1) % size;
  src_rank = (rank - 1) % size;
  printf("rank[%d]: %d %d", rank, dest_rank, src_rank);
  rank_value = rank;
  do {
    sum += rank_value;
    code = MPI_Isend(&rank_value, 1, MPI_INTEGER, dest_rank, tag, MPI_COMM_WORLD, &request);
    code = MPI_Irecv(&rank_value, 1, MPI_INTEGER, src_rank, tag, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
  } while(rank != rank_value);
  printf("Proc %d sum  = %d\n", rank, sum);
  MPI_Finalize();
  return 0;
}