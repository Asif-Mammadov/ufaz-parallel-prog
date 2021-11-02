#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#define NAME_MAX_LENGTH 129
int main (int argc, char ** argv)
{
int rank, size;
char hostname[NAME_MAX_LENGTH];

MPI_Init (&argc, &argv); /* starts MPI */
MPI_Comm_rank (MPI_COMM_WORLD, &rank); /* get current process id */
MPI_Comm_size (MPI_COMM_WORLD, &size); /* get number of processes */
gethostname(hostname, NAME_MAX_LENGTH);/* get hostname */


printf("Hello world from process %d size=%d on machine %s\n",rank,size,hostname);
MPI_Finalize();
return 0;
}