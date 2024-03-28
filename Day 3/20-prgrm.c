#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    int readerID = *((int *)arg);

    while (1) {
        sem_wait(&mutex);
        read_count++;

        if (read_count == 1) {
            sem_wait(&wrt);
        }

        sem_post(&mutex);
        printf("Reader %d is reading.\n", readerID);

        sem_wait(&mutex);
        read_count--;

        if (read_count == 0) {
            sem_post(&wrt);
        }

        sem_post(&mutex); 
        usleep(100000);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writerID = *((int *)arg);

    while (1) {
        sem_wait(&wrt);

       
        printf("Writer %d is writing.\n", writerID);

        sem_post(&wrt); 
        usleep(150000);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIDs[NUM_READERS], writerIDs[NUM_WRITERS];

    sem_init(&mutex, 0, 1); 
    sem_init(&wrt, 0, 1);   
    for (int i = 0; i < NUM_READERS; i++) {
        readerIDs[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)&readerIDs[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIDs[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void *)&writerIDs[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex); 
    sem_destroy(&wrt);   

    return 0;
}