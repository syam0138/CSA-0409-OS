#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fileDescriptor;
    char buffer[100];

    fileDescriptor = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fileDescriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    write(fileDescriptor, "Hello, this is a sample file.\n", 30);

    lseek(fileDescriptor, 0, SEEK_SET); 
    read(fileDescriptor, buffer, 30);
    printf("Read from file: %s", buffer);

    lseek(fileDescriptor, 10, SEEK_SET);
    write(fileDescriptor, "modified", 8);
    lseek(fileDescriptor, 0, SEEK_SET);

    read(fileDescriptor, buffer, 30);
    printf("Modified content: %s", buffer);

    close(fileDescriptor);

    return 0;
}