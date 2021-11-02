#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
  int rank, code, tag = 100;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */

  if (rank == 0) {
    int a,b, sum;
    printf("Enter value for a: "); 
    fflush(stdout);
    scanf("%d", &a);
    printf("Enter value for b: ");
    fflush(stdout);
    scanf("%d", &b);
    printf("Calculation...\n");
    fflush(stdout);
    MPI_Send(&a, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD); 
    MPI_Send(&b, 1, MPI_INTEGER, 1, tag, MPI_COMM_WORLD); 
	  MPI_Recv(&sum, 1, MPI_INTEGER,1,tag, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
    printf("Sum is : %d\n", sum);
    fflush(stdout);
  } else if (rank == 1) {
    int a, b, sum;
	  MPI_Recv(&a, 1, MPI_INTEGER,0,tag, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
	  MPI_Recv(&b, 1, MPI_INTEGER,0,tag, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
    sum = a+b;
    MPI_Send(&sum, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD); 
  }
  MPI_Finalize();
  return 0;
}