#include <stdio.h>


int main(void)
{
  double sum;
  double sum_local;
  double a[256], b[256];
  int numprocs, myid, my_first, my_last;
  int n = 256;

  MPI_Init();
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  my_first = myid * n/numprocs;
  my_last = (myid + 1) * n/numprocs;

 
  for (int i = 0; i < n; ++i)
  {
    a[i] = i * 0.5;
    b[i] = i * 2.0;
  }

  sum_local = 0;
  for (i = my_first; i < my_last; ++i)
  {
    sum_local += a[i]*b[i];
  }
  MPI_Allreduce(&sum_local, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
  
  if(iam == 0) printf("sum = %f\n", sum);
}
