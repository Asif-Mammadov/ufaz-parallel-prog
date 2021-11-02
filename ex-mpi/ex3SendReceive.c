#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main (int argc, char ** argv)  
{
  int rank, size,value,code,tag=100;
  MPI_Init (&argc, &argv);	/* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
  
  if (rank == 0) {
	value=1000;
	code=MPI_Send(&value,1, MPI_INTEGER,1,tag, MPI_COMM_WORLD);
  }
 else if (rank == 1) 
 {
	code=MPI_Recv(&value,1, MPI_INTEGER,0,tag, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
	printf("Process 1, has received %d from process 0 with code %d\n",value, code);
}
  MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */
  MPI_Finalize();
  return 0;
}