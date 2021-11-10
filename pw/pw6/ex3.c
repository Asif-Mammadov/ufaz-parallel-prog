#include <stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define SIZE 100
#define RANDOM_LIMIT 11 // included

void generate_array(int *a, int size){
  srand(time(NULL)); 
  for (int i = 0; i < size; i++){
    a[i] = rand() % (RANDOM_LIMIT + 1);
  }
}

int factorial(int n) {
  int prod = 1;
  for (int i = 1; i <= n; i++)
    prod *= i;
  return prod;
} 

void display_array(int *a, int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", a[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  int size, rank, nproc, code, block_length, tag = 200;
  double start_time, end_time;
  if (argc > 1)
    size = atoi(argv[1]);
  else 
    size = SIZE;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int *n = (int*)malloc(size * sizeof(int));
  block_length = (int) ceil(size * 1.0/nproc);
  int *block = (int*)malloc(block_length * sizeof(int));
  int *res = (int*)malloc(size * sizeof(int));
  if (rank == 0) {
    printf("Array size : %d\n", size);
    generate_array(n, size);
    start_time = MPI_Wtime();
  }
  MPI_Scatter(n, block_length, MPI_INTEGER, block, block_length, MPI_INTEGER, 0, MPI_COMM_WORLD);
  int a;
  for (int i = 0; i < block_length; i++){
    block[i] = factorial(block[i]);
  }
  MPI_Gather(res, block_length, MPI_INTEGER, res, block_length, MPI_INTEGER, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    end_time = MPI_Wtime();
    printf("Execution time: %lf\n", end_time - start_time);
  }
  MPI_Finalize();
  return 0;
}