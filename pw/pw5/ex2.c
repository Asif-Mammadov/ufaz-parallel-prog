#include <stdio.h>
#include<mpi.h>

int main(int argc, char **argv) {
  int rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("I am process %d, my rank is %s\n", rank, rank % 2 == 0 ? "even" : "odd");
  MPI_Finalize();
  return 0;
}