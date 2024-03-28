#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

struct File {
    char name[MAX_FILENAME_LENGTH];
    int size;
};

struct File files[MAX_FILES];
int totalFiles = 0;

void createFile(char name[], int size) {
    if (totalFiles < MAX_FILES) {
        strcpy(files[totalFiles].name, name);
        files[totalFiles].size = size;
        totalFiles++;
        printf("File '%s' created successfully.\n", name);
    } else {
        printf("Error: Maximum number of files reached.\n");
    }
}

void deleteFile(char name[]) {
    int found = 0;

    for (int i = 0; i < totalFiles; i++) {
        if (strcmp(files[i].name, name) == 0) {
            found = 1;

            for (int j = i; j < totalFiles - 1; j++) {
                strcpy(files[j].name, files[j + 1].name);
                files[j].size = files[j + 1].size;
            }

            totalFiles--;
            printf("File '%s' deleted successfully.\n", name);
            break;
        }
    }

    if (!found) {
        printf("Error: File '%s' not found.\n", name);
    }
}

void listFiles() {
    if (totalFiles == 0) {
        printf("No files in the directory.\n");
    } else {
        printf("Files in the directory:\n");
        for (int i = 0; i < totalFiles; i++) {
            printf("File %d: %s (Size: %d)\n", i + 1, files[i].name, files[i].size);
        }
    }
}

int main() {
    int choice;
    char filename[MAX_FILENAME_LENGTH];
    int size;

    while (1) {
        printf("\nSingle-Level Directory Operations:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the filename: ");
                scanf("%s", filename);
                printf("Enter the size of the file: ");
                scanf("%d", &size);
                createFile(filename, size);
                break;

            case 2:
                printf("Enter the filename to delete: ");
                scanf("%s", filename);
                deleteFile(filename);
                break;

            case 3:
                listFiles();
                break;

            case 4:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}