#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>

#define SIZE 1000
void generate_num(float *a, int size){
  srand(time(NULL)); 
  for (int i = 0; i < size; i++){
    a[i] = (float) rand() * 1000000 / RAND_MAX;
  }
}
int main(int argc, char **argv) {
  double start_time, end_time;
  int rank, code, tag = 200;
  int size = (argc > 1) ? atoi(argv[1]) : SIZE;
  float *a = (float*)malloc(size * sizeof(float));
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0){
    printf("Chosen size : %d\n", size);
    generate_num(a, size);
    start_time = MPI_Wtime();
    for (int i = 0; i < 9; i++){
      code = MPI_Send(a, size, MPI_FLOAT, 1, tag, MPI_COMM_WORLD);
      code = MPI_Recv(a, size, MPI_FLOAT, 1, tag, MPI_COMM_WORLD, NULL);
    }
    end_time = MPI_Wtime();
    printf("Execution : %f\n", end_time - start_time);
  } else if (rank == 1){
    for (int i = 0; i < 9; i++) {
      code = MPI_Recv(a, size, MPI_FLOAT, 0, tag, MPI_COMM_WORLD, NULL);
      code = MPI_Send(a, size, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}