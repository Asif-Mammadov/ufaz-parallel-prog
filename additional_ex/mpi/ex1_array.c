#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
  int rank, code, tag = 100;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */

  if (rank == 0) {
    int v[2], sum;
    printf("Enter value for a: "); 
    fflush(stdout);
    scanf("%d", &v[0]);
    printf("Enter value for b: ");
    fflush(stdout);
    scanf("%d", &v[1]);
    printf("Calculation...\n");
    fflush(stdout);
    MPI_Send(v, 2, MPI_INTEGER, 1, tag, MPI_COMM_WORLD); 
	  MPI_Recv(&sum, 1, MPI_INTEGER,1,tag, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
    printf("Sum is : %d\n", sum);
    fflush(stdout);
  } else if (rank == 1) {
    int v[2], sum;
	  MPI_Recv(v, 1, MPI_INTEGER,0,tag, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
    sum = v[0] + v[1];
    MPI_Send(&sum, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD); 
  }
  MPI_Finalize();
  return 0;
}