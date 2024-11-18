#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int x;
sem_t sem_p;
sem_t sem_q;
sem_t sem_r;

void *p(void *arg)
{
  for (int i = 1; i <= 10; i++)
  {
    sem_wait(&sem_p);
    x = i;
    if (x % 2 == 0)
    {
      sem_post(&sem_r);
    }
    else
    {
      sem_post(&sem_q);
    }
  }
  return NULL;
}

void *q(void *arg)
{
  for (int i = 0; i < 5; i++)
  {
    sem_wait(&sem_q);
    printf("Nieparzyste: %d\n", x);
    sem_post(&sem_p);
  }
  return NULL;
}

void *r(void *arg)
{
  for (int i = 0; i < 5; i++)
  {
    sem_wait(&sem_r);
    printf("Parzyste: %d\n", x);
    sem_post(&sem_p);
  }
  return NULL;
}

int main()
{
  pthread_t thread_p, thread_q, thread_r;

  sem_init(&sem_p, 0, 1);
  sem_init(&sem_q, 0, 0);
  sem_init(&sem_r, 0, 0);

  pthread_create(&thread_p, NULL, p, NULL);
  pthread_create(&thread_q, NULL, q, NULL);
  pthread_create(&thread_r, NULL, r, NULL);

  pthread_join(thread_p, NULL);
  pthread_join(thread_q, NULL);
  pthread_join(thread_r, NULL);

  sem_destroy(&sem_p);
  sem_destroy(&sem_q);
  sem_destroy(&sem_r);

  return 0;
}
