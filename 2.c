#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define iter 5

int x;

sem_t gotowe_do_zapisu;
sem_t gotowe_do_wypisania;

void *p(void *l)
{
  int j = 0;
  for (int i = 0; i < iter; i++)
  {
    sem_wait(&gotowe_do_zapisu);
    j += 2;
    x = j;
    printf("P zapisał: %d\n", x);
    sem_post(&gotowe_do_wypisania);
  }
  return NULL;
}

void *q(void *l)
{
  int j = -1;
  for (int i = 0; i < iter; i++)
  {
    sem_wait(&gotowe_do_zapisu);
    j += 2;
    x = j;
    printf("Q zapisał: %d\n", x);
    sem_post(&gotowe_do_wypisania);
  }
  return NULL;
}

void *r(void *l)
{
  for (int i = 0; i < 2 * iter; i++)
  {
    sem_wait(&gotowe_do_wypisania);
    printf("R wypisał: %d\n", x);
    sem_post(&gotowe_do_zapisu);
  }
  return NULL;
}

int main()
{
  pthread_t w1, w2, w3;

  sem_init(&gotowe_do_zapisu, 0, 1);
  sem_init(&gotowe_do_wypisania, 0, 0);

  pthread_create(&w1, NULL, p, NULL);
  pthread_create(&w2, NULL, q, NULL);
  pthread_create(&w3, NULL, r, NULL);

  pthread_join(w1, NULL);
  pthread_join(w2, NULL);
  pthread_join(w3, NULL);

  sem_destroy(&gotowe_do_zapisu);
  sem_destroy(&gotowe_do_wypisania);

  return 0;
}
