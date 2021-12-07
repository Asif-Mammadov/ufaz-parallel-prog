#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
#include<limits.h>

#define SIZE 1000
#define RANDOM_LIMIT 1000000 // included
void generate_array(int *a, int size){
  srand(time(NULL)); 
  for (int i = 0; i < size; i++){
    a[i] = rand() % (RANDOM_LIMIT + 1);
  }
}

int max(int n1, int n2){
  if (n1 > n2)
    return n1;
  return n2;
}

int main(int argc, char **argv) {
  int rank, nproc, block_size, local_max, global_max;
  int *a = (int*)malloc(SIZE * sizeof(int));
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  block_size = (int) ceil(SIZE * 1.0/nproc);
  int *data_block = (int*)malloc(block_size * sizeof(int));
  int *max_array = (int*)malloc(nproc * sizeof(int));
  if (rank == 0) {
    generate_array(a, SIZE);
  }
  MPI_Scatter(a, block_size, MPI_INTEGER, 
  data_block, block_size, MPI_INTEGER, 0, MPI_COMM_WORLD);

  local_max = INT_MIN;
  for (int i = 0; i < block_size; i++)
    local_max = max(data_block[i], local_max);

  MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); 
  if (rank == 0)
    printf("Global Max = %d\n", global_max);
  MPI_Finalize();
  return 0;
}