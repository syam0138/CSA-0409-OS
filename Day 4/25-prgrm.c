#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Open a file
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    // Read and print file content
    char buffer[100];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    
    // Seek to a specific position in the file
    off_t offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    
    // Get file information using stat
    struct stat file_info;
    if (fstat(fd, &file_info) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }
    printf("\nFile size: %ld bytes\n", file_info.st_size);
    printf("File permissions: %o\n", file_info.st_mode & 0777);
    
    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    // Open a directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

 
    struct dirent *entry;
    printf("\nDirectory contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    if (closedir(dir) == -1) {
        perror("closedir");
        exit(EXIT_FAILURE);
    }

    return 0;
}