#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main (int argc, char ** argv)  
{
  int rank, size,sum,code;
  int * data;
  MPI_Init (&argc, &argv);	/* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  data=(int *)malloc(size*sizeof(int));
  data[rank]=rank;
  MPI_Reduce(&data[rank],&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
  if (rank == 0) 
	{ 
		printf("Me, procces 0, Sum = %d \n",sum);
	}  
  MPI_Finalize(); 
  return 0;
}