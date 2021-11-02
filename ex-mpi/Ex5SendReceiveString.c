#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <string.h>
#define max 100
int main (int argc, char ** argv)
  
{
  int rank, size,code,tag=100,count;
  MPI_Status status;
  char data [100];
   

  MPI_Init (&argc, &argv);	/* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
  
  if (rank == 0) {
  	printf("Message=?\n");
	scanf("%s",data);
	code=MPI_Send(data,strlen(data), MPI_CHAR,1,tag, MPI_COMM_WORLD);
  }
 else if (rank == 1) 
 {
 code=MPI_Recv(data,100, MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD,&status);
 MPI_Get_count(&status, MPI_CHAR,&count);
 printf("Source=%d tag=%d count=%d\n",status.MPI_SOURCE,status.MPI_TAG,count);	
 printf("Me, process 1, i have received %s from processus %d.\n",data,status.MPI_SOURCE);
}

  MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */
  
  MPI_Finalize();
 
 
  return 0;
}