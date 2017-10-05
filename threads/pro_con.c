#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define MAX_SIZE 10
int buffer[MAX_SIZE];

sem_t ready; // Inicia en 0, indica que hay algo que consumir
sem_t slots;

int get_rand(float max)
{
    return 1 + (rand() * max) / RAND_MAX;
}

void *producer(void *threadid)
{
    int i = 0;
    for (;;)
    {
        sem_wait(&slots);
        buffer[i] = get_rand(10.0);
        printf("Produced: %d\n", buffer[i]);
        sem_post(&ready);
        i = (i + 1) % MAX_SIZE;
    }
    pthread_exit(NULL);
}

void *consumer(void *threadid)
{
    int i = 0, value;
    for (;;)
    {
        sem_wait(&ready);
        value = buffer[i];
        printf("Consumed: %d\n", value);
        sem_post(&slots);
        i = (i + 1) % MAX_SIZE;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t ptconsumer, ptproducer;
    int rc;

    sem_init(&ready, 0, 0);
    sem_init(&slots, 0, MAX_SIZE);

    rc = pthread_create(&ptconsumer, NULL, consumer, NULL);
    rc += pthread_create(&ptproducer, NULL, producer, NULL);
    if (rc)
    {
        exit(-1);
    }
    pthread_exit(NULL);
}