#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
int isprime(int n)
{
  int i, squareroot;
  if (n > 10)
  {
    squareroot = (int)sqrt(n);
    for (i = 3; i <= squareroot; i = i + 2)
      if ((n % i) == 0)
        return 0;
    return 1;
  } /* Assume first four primes are counted elsewhere. Forget everything else */
  else
    return 0;
}
int main(int argc, char **argv)
{
  int rank;
  int nproc;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  int pmax = 1000000;
  int block_size = (int) ceil(1.0 * pmax/nproc); 

  for (int i = rank*block_size; i < (rank+1) * block_size; i++) {
    if(isprime(i))
      printf("Process %d : Prime : %d\n", rank, i);
  }
  MPI_Finalize();
  return 0;
}