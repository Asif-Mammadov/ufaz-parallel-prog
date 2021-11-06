#include<stdio.h>
#include<mpi.h>

int factorial(int n) {
  if (n == 1) 
    return 1;
  return n * factorial(n-1);
}
int main(int argc, char **argv) {
  int rank, n, code, tag = 200, res;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    printf("Enter the number: ");
    fflush(stdout);
    scanf("%d", &n);
    code = MPI_Send(&n, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
    code = MPI_Recv(&res, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, NULL);
    printf("%d! = %d\n", n, res);
  } else if (rank == 1) {
    code = MPI_Recv(&n, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, NULL);
    res = factorial(n);
    code = MPI_Send(&res, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}