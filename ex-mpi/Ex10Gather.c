#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>  
int main(int argc, char *argv[]) {
    int rank, nprocs,block_length,nb_values=8;
	int * data,* values;	
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 	
	block_length=nb_values/nprocs;
	data=(int*)malloc(nb_values*sizeof(int));
	values=(int*)malloc(block_length*sizeof(int));	
	for(int i=0;i<block_length;i++)	{
		values[i]=1000+i+(rank*block_length);
	    printf("Process %d send %d\n",rank,values[i]);fflush(stdout);
	}
	MPI_Gather(values,block_length, MPI_REAL,data,block_length,  MPI_REAL,nprocs-1, MPI_COMM_WORLD);
	if (rank==nprocs-1 ){
		printf( "Me, Process %d i have received data: ",rank); 
		for(int i=0;i<nb_values;i++)
			printf("%d,",data[i]);fflush(stdout);
		printf("\n");
	}
    MPI_Finalize(); 
    return 0; 
} 