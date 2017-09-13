#define NUMTHREADS 4

double sum;
double a[256], b[256];
int status;
int n = 256;

pthread_t thd[NUMTHREADS];
pthread_mutex_t mutexsum;


void * dotprod (void *arg)
{
  int myid, i, my_first, my_last;
  double sum_local;

  myid = (int)arg;
  my_first = myid * n/NUMTHREADS;
  my_last = (myid + 1) * n/NUMTHREADS;

  sum_local = 0;
  for (int i = my_first; i < my_last; ++i)
  {
    sum_local += a[i]*b[i];
  }
  pthread_mutex_lock (&mutex_sum);
  sum += sum_local;
  pthread_mutex_unlock (&mutex_sum);

  pthread_exit((void*)0);
}


int main ()
{
  pthread_attr_t attr;
  
  for (i = 0; i < n; ++i)
  {
    a[i] = i * 0.5;
    b[i] = i * 2.0;
  }

  thread_mutex_init(&mutexsum, NULL);
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < NUMTHREADS; ++i)
  {
    pthread_create(&thds[i], &attr, dotprod, (void*)i);
  }
  pthread_attr_destroy(&attr);

  for (i = 0; i < NUMTHREADS; ++i)
  {
    pthread_join(thds[i], (void**)&status);
  }

  printf("sum = %f\n", sum);
  pthread_mutex_destroy(&mutexsum);
  pthread_exit(NULL);
}
