#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h> 
#define n 1000
int main(int argc, char *argv[]) {
    int rank, nprocs,block_length,totalSum;
	int * data,* dataBlock,* sum;
	
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 	
	block_length=n/nprocs;
	data=(int*)malloc(n*sizeof(int));
	dataBlock=(int*)malloc(block_length*sizeof(int));
	sum =(int *) malloc(nprocs*sizeof(int));	
	if (rank == 0){
		for(int i=0;i<n;i++)
			data[i]=i;
	}
	MPI_Scatter(data,block_length, MPI_INT,dataBlock,block_length, MPI_INT,0, MPI_COMM_WORLD);
    printf( "Start computing for %d\n",rank); fflush(stdout);
	int s=0;
	for(int i=0;i<block_length;i++)
		s+=dataBlock[i];	
	printf("local sum for proces %d =%d\n",rank,s);fflush(stdout);
	MPI_Gather(&s,1,MPI_INT,sum,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)	{
		totalSum=0;
		for(int i=0;i<nprocs;i++)
			totalSum+=sum[i];
		printf("Sum=%d\n",totalSum);fflush(stdout);
	}
    MPI_Finalize(); 
    return 0; 
} 