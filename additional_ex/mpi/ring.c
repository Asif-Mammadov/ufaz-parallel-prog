// #include <stdio.h>
// #include <mpi.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
//   int rank, size;
//   int n, tag = 200;
//   MPI_Init(&argc, &argv);
//   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//   MPI_Comm_size(MPI_COMM_WORLD, &size);

//   if (rank == 0)
//   {
//     printf("rank %d", rank);
//     MPI_Send(&rank, 1, MPI_INTEGER, (rank + 1) % size, tag, MPI_COMM_WORLD);
//     MPI_Recv(&n, 1, MPI_INTEGER, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

//     printf("Done! Sum : %d\n", n);
//   }
//   for (int i = 1; i < size - 1; i++)
//   {
//     if (rank == i)
//     {
//       n += rank;
//       MPI_Recv(&n, 1, MPI_INTEGER, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//       MPI_Send(&n, 1, MPI_INTEGER, (rank + 1) % size, tag, MPI_COMM_WORLD);
//     }
//   }
//   MPI_Finalize();
//   return 0;
// }


#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include<time.h>
int main (int argc, char **argv) {
  int rank, size, val, sum, tag = 200;
  int leftid, rightid;
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  leftid = rank - 1;
  rightid = rank + 1;
  if (rank == 0)
    leftid = size - 1;
  else if (rank == size - 1)
    rightid = 0;
  
  printf("I am process number %d sending to %d and receiving from %d\n", rank, rightid, leftid);
  srand(time(0));
  val = rand() % 1000;
  printf("Process: %d Value : %d\n", rank, val);
  if (rank == 0){
    MPI_Send(&val, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD);
    MPI_Recv(&sum, 1, MPI_INTEGER, leftid, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Sum = %d\n", sum);
  } else {
    MPI_Recv(&sum, 1, MPI_INTEGER, leftid, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    sum += val;
    MPI_Send(&sum, 1, MPI_INTEGER, rightid, tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
}