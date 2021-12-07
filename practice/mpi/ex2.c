#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv) {
  int a, b, sum, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    printf("Give 2 numbers:\n"); fflush(stdout);
    scanf("%d %d", &a, &b);
    MPI_Send(&a, 1, MPI_INT, 1, 200, MPI_COMM_WORLD);
    MPI_Send(&b, 1, MPI_INT, 1, 200, MPI_COMM_WORLD);
    MPI_Recv(&sum, 1, MPI_INT, 1, 200, MPI_COMM_WORLD, NULL);
    printf("Sum = %d\n", sum);
  } else if (rank == 1) {
    MPI_Recv(&a, 1, MPI_INT, 0, 200, MPI_COMM_WORLD, NULL);
    MPI_Recv(&b, 1, MPI_INT, 0, 200, MPI_COMM_WORLD, NULL);
    sum = a + b;
    MPI_Send(&sum, 1, MPI_INT,0, 200, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}