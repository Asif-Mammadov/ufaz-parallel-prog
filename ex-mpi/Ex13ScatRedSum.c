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
	sum[rank]=0;
	for(int i=0;i<block_length;i++)
		sum[rank]+=dataBlock[i];	
	printf("local sum for procces %d =%d\n",rank,sum[rank]);fflush(stdout);
	MPI_Reduce(&sum[rank],&totalSum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)	{
		printf("Sum=%d\n",totalSum);fflush(stdout);
	}
    MPI_Finalize(); 
    return 0; 
} 