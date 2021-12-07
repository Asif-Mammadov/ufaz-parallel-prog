#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define SIZE 100
void generate(int* a, int size) {
  for (int i = 0; i < size; i++) {
    a[i] = i;
  }
}

int main(int argc, char **argv) {
  int block_size, rank, nproc, local_sum, global_sum;
  MPI_Init(&argc, &argv);
  int *a = (int*) malloc(SIZE * sizeof(int));
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  block_size = SIZE / nproc;
  int *sums = (int*) malloc(nproc * sizeof(int));
  int *data_block = (int*) malloc(block_size * sizeof(int));
  if (rank == 0) {
    generate(a, SIZE);
  }
  MPI_Scatter(a, block_size, MPI_INT, data_block, block_size, MPI_INT, 0, MPI_COMM_WORLD);

  local_sum = 0;
  for (int i = 0; i < block_size; i++) {
    local_sum += data_block[i];
  }
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  MPI_Bcast(&global_sum, nproc, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank == 2) {
    printf ("Rank %d\n", rank);
    printf("Global sum : %d\n", global_sum);
  }
  MPI_Finalize();
  return 0;
}