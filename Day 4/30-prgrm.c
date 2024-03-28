#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    printf("Hello from the new thread!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t createThread;
    if (pthread_create(&createThread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1; 
    }

    pthread_t joinThread;
    if (pthread_create(&joinThread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1; 
    }

    if (pthread_join(joinThread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 1; 
    }

    pthread_t equalThread1, equalThread2;
    if (pthread_create(&equalThread1, NULL, threadFunction, NULL) != 0 ||
        pthread_create(&equalThread2, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating threads\n");
        return 1; 
    }

    if (pthread_equal(equalThread1, equalThread2)) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    pthread_join(equalThread1, NULL);
    pthread_join(equalThread2, NULL);

    pthread_t exitThread;
    if (pthread_create(&exitThread, NULL, threadFunction, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1; 
    }
    if (pthread_join(exitThread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 1; 
    }

    printf("Back in the main thread\n");

    pthread_exit(NULL);

    return 0; 
}