#include <stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 1000
#define RANDOM_LIMIT 10 // included

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
  int size, rank, code, tag = 200;
  double start_time, end_time;
  if (argc > 1)
    size = atoi(argv[1]);
  else 
    size = SIZE;
  int *n = (int*)malloc(size * sizeof(int));
  int *res = (int*)malloc(size * sizeof(int));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    printf("Array size : %d\n", size);
    generate_array(n, size);
    start_time = MPI_Wtime();
    code = MPI_Send(n, size, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
    code = MPI_Recv(res, size, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, NULL);
    end_time = MPI_Wtime();
    printf("Execution time: %lf\n", end_time - start_time);
  } else if (rank == 1) {
    code = MPI_Recv(n, size, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, NULL);
    for (int i = 0; i < size; i++){
      res[i] = factorial(n[i]);
    }
    code = MPI_Send(res, size, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}