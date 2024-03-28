#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

struct Record {
    int id;
    char data[50];
};

int main() {
    FILE *file;
    struct Record records[MAX_RECORDS];
    int numRecords;

    printf("Enter the number of records: ");
    scanf("%d", &numRecords);

    file = fopen("sequential_file.dat", "wb");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Enter the records:\n");
    for (int i = 0; i < numRecords; ++i) {
        printf("Record %d:\n", i + 1);
        records[i].id = i + 1;
        printf("Enter data: ");
        scanf("%s", records[i].data);

        fwrite(&records[i], sizeof(struct Record), 1, file);
    }

    fclose(file);

    file = fopen("sequential_file.dat", "rb");

    if (file == NULL) {
        perror("Error opening file for reading");
        return 1; 
    }

    printf("\nReading records:\n");
    for (int i = 0; i < numRecords; ++i) {
        fread(&records[i], sizeof(struct Record), 1, file);
        printf("Record %d: %s\n", records[i].id, records[i].data);
    }

    fclose(file);

    return 0; 
}