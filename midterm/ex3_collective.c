#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char **argv) {
  int rank, size, tag = 100;
  float avr = 0, value;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  float *dev = (float*) malloc(size * sizeof(float));
  value = rank;
  MPI_Gather(&value, 1, MPI_REAL, dev, 1, MPI_REAL, 0, MPI_COMM_WORLD); 
  if (rank == 0) {
    for (int i = 0; i < size; i++) 
      avr += dev[i];
    avr /= size;
    for (int i = 0; i < size; i++) 
      dev[i] -= avr;
    
    printf("The average is %f\n", avr);
    for (int i = 0; i < size; i++) 
      printf("Deviation[%d] = %f\n", i, dev[i]);
  }
  MPI_Finalize();
  return 0;
}