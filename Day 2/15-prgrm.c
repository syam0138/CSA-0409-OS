#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50
#define MAX_DIRECTORIES 50
#define MAX_DIR_NAME_LENGTH 50

struct File {
    char name[MAX_FILENAME_LENGTH];
    int size;
};

struct Directory {
    char name[MAX_DIR_NAME_LENGTH];
    struct File files[MAX_FILES];
    int totalFiles;
};

struct Directory rootDirectory[MAX_DIRECTORIES];
int totalDirectories = 0;

void createDirectory(char dirName[]) {
    if (totalDirectories < MAX_DIRECTORIES) {
        strcpy(rootDirectory[totalDirectories].name, dirName);
        rootDirectory[totalDirectories].totalFiles = 0;
        totalDirectories++;
        printf("Directory '%s' created successfully.\n", dirName);
    } else {
        printf("Error: Maximum number of directories reached.\n");
    }
}

void createFile(char dirName[], char fileName[], int size) {
    int dirIndex = -1;

    for (int i = 0; i < totalDirectories; i++) {
        if (strcmp(rootDirectory[i].name, dirName) == 0) {
            dirIndex = i;
            break;
        }
    }

    if (dirIndex != -1) {
        struct Directory *currentDirectory = &rootDirectory[dirIndex];

        if (currentDirectory->totalFiles < MAX_FILES) {
            strcpy(currentDirectory->files[currentDirectory->totalFiles].name, fileName);
            currentDirectory->files[currentDirectory->totalFiles].size = size;
            currentDirectory->totalFiles++;
            printf("File '%s' created in directory '%s' successfully.\n", fileName, dirName);
        } else {
            printf("Error: Maximum number of files reached in directory '%s'.\n", dirName);
        }
    } else {
        printf("Error: Directory '%s' not found.\n", dirName);
    }
}

void listFilesInDirectory(char dirName[]) {
    int dirIndex = -1;

    for (int i = 0; i < totalDirectories; i++) {
        if (strcmp(rootDirectory[i].name, dirName) == 0) {
            dirIndex = i;
            break;
        }
    }

    if (dirIndex != -1) {
        struct Directory *currentDirectory = &rootDirectory[dirIndex];

        if (currentDirectory->totalFiles == 0) {
            printf("No files in directory '%s'.\n", dirName);
        } else {
            printf("Files in directory '%s':\n", dirName);
            for (int i = 0; i < currentDirectory->totalFiles; i++) {
                printf("File %d: %s (Size: %d)\n", i + 1, currentDirectory->files[i].name,
                       currentDirectory->files[i].size);
            }
        }
    } else {
        printf("Error: Directory '%s' not found.\n", dirName);
    }
}

int main() {
    int choice;
    char dirName[MAX_DIR_NAME_LENGTH];
    char fileName[MAX_FILENAME_LENGTH];
    int size;

    while (1) {
        printf("\nTwo-Level Directory Operations:\n");
        printf("1. Create Directory\n");
        printf("2. Create File\n");
        printf("3. List Files in Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the directory name: ");
                scanf("%s", dirName);
                createDirectory(dirName);
                break;

            case 2:
                printf("Enter the directory name: ");
                scanf("%s", dirName);
                printf("Enter the filename: ");
                scanf("%s", fileName);
                printf("Enter the size of the file: ");
                scanf("%d", &size);
                createFile(dirName, fileName, size);
                break;

            case 3:
                printf("Enter the directory name: ");
                scanf("%s", dirName);
                listFilesInDirectory(dirName);
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