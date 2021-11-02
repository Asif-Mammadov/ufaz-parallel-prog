#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main(int argc, char **argv)

{
  int rank, size, code, tag = 100;
  int a, b, c;

  MPI_Init(&argc, &argv);               /* starts MPI */
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get current process id */

  if (rank == 0)
  {
    printf("Process %d, Give a\n", rank);
    scanf("%d", &a);
    printf("Process %d, Give b\n", rank);
    scanf("%d", &b);
    code = MPI_Send(&a, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
    code = MPI_Send(&b, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);

    code = MPI_Recv(&c, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    printf("Process %d,Result=%d\n", rank, c);
  }
  else if (rank == 1)
  {
    code = MPI_Recv(&a, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    code = MPI_Recv(&b, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    c = a + b;
    code = MPI_Send(&c, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD);
  }

  MPI_Comm_size(MPI_COMM_WORLD, &size); /* get number of processes */

  MPI_Finalize();

  return 0;
}