#include <stdio.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char content[] = "Hello, this is a sample file content.";

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return 1; 
    }

    fprintf(file, "%s\n", content);

    fclose(file);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file %s for reading\n", filename);
        return 1; 
    }
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    printf("File content: %s", buffer);

    fclose(file);

    return 0;
}