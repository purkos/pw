#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t gotowe_do_wypisania;
sem_t gotowe_do_zapisu;
int x;

void* producent(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&gotowe_do_zapisu);
        x = i;
        sem_post(&gotowe_do_wypisania);
    }
    return NULL;
}

void* konsument(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&gotowe_do_wypisania);
        printf("%d\n", x);
        sem_post(&gotowe_do_zapisu);
    }
    return NULL;
}

int main() {
    pthread_t p, q;



    sem_init(&gotowe_do_wypisania, 0, 0);
    sem_init(&gotowe_do_zapisu, 0, 1);

    pthread_create(&p, NULL, producent, NULL);
    pthread_create(&q, NULL, konsument, NULL);

    pthread_join(p, NULL);
    pthread_join(q, NULL);

    sem_destroy(&gotowe_do_wypisania);
    sem_destroy(&gotowe_do_zapisu);

    return 0;
}
