#include<stdio.h>
#include<mpi.h>
#include <time.h>
#include<stdlib.h>

#define RANDOM_LIMIT 100
#define SIZE 1000
float make_random(int limit) {
  return ((float)rand()/(float)(RAND_MAX)) * (float) limit;
}

void generate(float *a, int size) {
  srand(time(NULL)); 
  for (int i = 0; i < size; i++)
    a[i] = make_random(RANDOM_LIMIT);
}

int main(int argc, char **argv) {
  double start_time, end_time;
  int code, rank;
  float *a = (float*) malloc (SIZE * sizeof(float));
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  start_time = MPI_Wtime();
  if (rank == 0) {
    generate(a, SIZE);
    code = MPI_Send(a, SIZE, MPI_REAL, 1, 200, MPI_COMM_WORLD);
  } else if (rank == 1) {
    code = MPI_Recv(a, SIZE, MPI_REAL, 0, 200, MPI_COMM_WORLD, NULL); 
    end_time = MPI_Wtime();
    for (int i = 0; i < SIZE; i++) 
      printf("%.2f ", a[i]);
    printf("\nExecution time %lf\n", end_time - start_time);
  }
  MPI_Finalize();
  return 0;
}