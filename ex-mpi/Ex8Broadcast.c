#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main (int argc, char ** argv)  
{
  int rank, value=0,code;
  MPI_Init (&argc, &argv);	/* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */  
  printf("Me, process %d before bcast. Value = %d\n", rank, value);
  if (rank == 1) {
	  value=rank+1000;
	  }
  code=MPI_Bcast(&value,1, MPI_INTEGER,1, MPI_COMM_WORLD);
  printf("Me, process %d , I have received %d from process 1.\n",rank,value);  
  MPI_Finalize(); 
  return 0;
}