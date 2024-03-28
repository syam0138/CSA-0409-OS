#include <stdio.h>
#include <sys/stat.h>

int main() {
    const char *filepath = "C:/Users/acer/Downloads/Human.Fall.Flat.v1086362/Human.Fall.Flat.v1086362/HOW TO RUN GAME!!.txt";

    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (chmod(filepath, permissions) == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        perror("Error changing file permissions");
        return 1;
    }

    return 0;
}