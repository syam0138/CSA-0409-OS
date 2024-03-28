#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int shared_variable = 0;

void *thread_function(void *thread_id) {
    int tid = *(int *)thread_id;
    
    // Acquire the mutex lock before accessing the shared variable
    pthread_mutex_lock(&mutex);
    printf("Thread %d: Shared variable before increment: %d\n", tid, shared_variable);
    
    // Increment the shared variable
    shared_variable++;
    printf("Thread %d: Shared variable after increment: %d\n", tid, shared_variable);
    
    // Release the mutex lock
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;
    
    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }
    
    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]) != 0) {
            printf("Thread creation failed\n");
            return 1;
        }
    }
    
    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Thread join failed\n");
            return 1;
        }
    }
    
    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    
    return 0;
}