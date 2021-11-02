#include<stdio.h>
#include<mpi.h>
#include <math.h>
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
int main(int argc, char *argv[]) {
  int rank, size, mystart, myend, stride;
  double start_time, end_time;
  int pmax = 10000000;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  mystart = (rank * 2) + 7;
  myend=(rank + 1) * (pmax/size);
  printf("Me process %d working with [%d %d]]\n", rank, mystart, myend);
  start_time = MPI_Wtime();
  for (int i = mystart; i <= pmax; i = i + size * 2)
  {
      if(isprime(i)) ;
      // printf("Process %d : Prime : %d\n", rank, i);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank==0){
    end_time = MPI_Wtime();
    printf("Execution time=%lf\n", end_time-start_time);
  }
  MPI_Finalize();
}