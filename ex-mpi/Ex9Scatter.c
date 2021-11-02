#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include<math.h>
int main(int argc, char *argv[]) 
{
    int rank, nprocs,block_length,nb_values=8;
	int * data,* values;	
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 	
	block_length= (int) ceil(nb_values * 1.0/nprocs);
	// block_length= nb_values/nprocs;
	data=(int*)malloc(block_length*sizeof(int));
	values=(int*)malloc(nb_values*sizeof(int));	
	if (rank == 0)
	{
		printf("Process %d, send the array values:",rank);fflush(stdout);
		for(int i=0;i<nb_values;i++)
		{
			values[i]=1000+i;
		    printf("%d,",values[i]);fflush(stdout);
		}
		printf("\n");fflush(stdout);
	}
	MPI_Scatter(values,block_length, MPI_INTEGER,data,block_length, MPI_INTEGER,0, MPI_COMM_WORLD);
    printf( "Process %d received data ",rank); 
	for(int i=0;i<block_length;i++)
		printf("%d,",data[i]);fflush(stdout);
	printf("from process 2\n");fflush(stdout);
    MPI_Finalize(); 
    return 0; 
} 