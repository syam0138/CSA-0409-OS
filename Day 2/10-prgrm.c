#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSAGE_QUEUE_KEY 1234
#define MESSAGE_SIZE 100

struct Message {
    long mtype; 
    char mtext[MESSAGE_SIZE];
};

int main() {
    int msqid;
    pid_t pid;

    msqid = msgget(MESSAGE_QUEUE_KEY, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {

        struct Message message;
        message.mtype = 1;

        snprintf(message.mtext, MESSAGE_SIZE, "Hello from the sender process!");

        if (msgsnd(msqid, &message, sizeof(message.mtext), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        wait(NULL);
    } else {

        struct Message message;

        if (msgrcv(msqid, &message, sizeof(message.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("Receiver Process: Received message: %s\n", message.mtext);

        exit(EXIT_SUCCESS);
    }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}