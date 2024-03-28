#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHARED_MEMORY_KEY 1234
#define SHARED_MEMORY_SIZE 100

struct SharedData {
    char message[SHARED_MEMORY_SIZE];
};

int main() {
    int shmid;
    pid_t pid;

    shmid = shmget(SHARED_MEMORY_KEY, sizeof(struct SharedData), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    struct SharedData *shared_data = (struct SharedData *)shmat(shmid, NULL, 0);
    if ((int)shared_data == -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        snprintf(shared_data->message, SHARED_MEMORY_SIZE, "Hello from the writer process!");

        wait(NULL);
    } else {
        printf("Reader Process: Received message: %s\n", shared_data->message);

        if (shmdt(shared_data) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}