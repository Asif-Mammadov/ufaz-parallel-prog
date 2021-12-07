#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main(int argc, char **argv) {
  int rank, size, tag = 100, value;
  int p[2];
  float avr = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  value = rank;
  if (rank == 0) {
    float *dev = (float*) malloc(size * sizeof(float));
    avr += value;
    dev[0] = value;
    for (int i = 1; i < size; i++) {
      MPI_Recv(&p, 2, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, NULL);
      avr += p[1];
      dev[p[0]] = p[1];
    }
    avr /= size;
    for (int i = 0; i < size; i++) {
      dev[i] -= avr;
    }
    printf("The average is %f\n", avr);
    for (int i = 0; i < size; i++) 
      printf("Deviation[%d] = %f\n", i, dev[i]);
  } else {
    p[0] = rank;
    p[1] = value;
    MPI_Send(&p, 2, MPI_INT, 0, tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}