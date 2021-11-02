#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
int main (int argc, char ** argv)
{
int rank, size;
MPI_Init (&argc, &argv); /* starts MPI */
MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */

if(rank==0)
{
	for(int i=0;i<10;i++)
	{
		sleep(1);
		printf( "Hello world from process %d count=%d\n", rank,i);	fflush(stdout);		
		if(i==5)
		     MPI_Abort(MPI_COMM_WORLD,-1);
	}
}
else if(rank==1)
	{
		for(int i=0;i<10;i++)
		{
			sleep(1);
			printf( "Hello world from process %d count=%d\n", rank,i);	fflush(stdout);	
		}
	}

MPI_Finalize();
return 0;
}
