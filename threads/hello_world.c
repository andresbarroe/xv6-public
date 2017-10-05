/******************************************************************************
* FILE: hello.c
* DESCRIPTION:
*   A "hello world" Pthreads program.  Demonstrates thread creation and
*   termination.
* AUTHOR: Blaise Barney
* LAST REVISED: 08/09/11
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 10

long saldo;
sem_t mutex;

void *PrintHello(void *threadid)
{
    long tid;
    long lsaldo;
    tid = (long)threadid;

    sem_wait(&mutex);
    /* Region Critica */
    lsaldo = saldo;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    sleep(1); // Forzar perder el CPU, simular carga
    lsaldo++;
    saldo = lsaldo;

    sem_post(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    saldo = 0;
    sem_init(&mutex, 0, 1);
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %ld\n", rc);
            exit(-1);
        }
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL); // En NULL puede ir una apuntador para obtener que regreso un thread
    }
    printf("Saldo: %d\n", saldo);
    /* Last thing that main() should do */
    pthread_exit(NULL); // Se pueden regresar valores a la funcion que creo esta thread
}