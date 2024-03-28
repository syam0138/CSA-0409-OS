#include <stdio.h>

#define MEMORY_SIZE 1000

struct Block {
    int size;
    int allocated;
};

void bestFit(struct Block memory[], int num_blocks, int process_size) {
    int best_fit_index = -1;
    int min_size = MEMORY_SIZE + 1;

    for (int i = 0; i < num_blocks; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size) {
            if (memory[i].size < min_size) {
                min_size = memory[i].size;
                best_fit_index = i;
            }
        }
    }

    if (best_fit_index != -1) {
        memory[best_fit_index].allocated = 1;
        printf("Process of size %d allocated at block %d.\n", process_size, best_fit_index);
    } else {
        printf("No suitable block found for process of size %d.\n", process_size);
    }
}

void printMemory(struct Block memory[], int num_blocks) {
    printf("Memory Blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: Size=%d, Allocated=%s\n", i, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
    printf("\n");
}

int main() {
    int num_blocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &num_blocks);

    struct Block memory[num_blocks];

    // Initialize memory blocks
    for (int i = 0; i < num_blocks; i++) {
        printf("Enter size of block %d: ", i);
        scanf("%d", &memory[i].size);
        memory[i].allocated = 0;
    }

    while (1) {
        int choice, process_size;
        printf("\nMemory Management Menu:\n");
        printf("1. Allocate Memory\n");
        printf("2. Print Memory Status\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size of the process to allocate: ");
                scanf("%d", &process_size);
                bestFit(memory, num_blocks, process_size);
                break;

            case 2:
                printMemory(memory, num_blocks);
                break;

            case 3:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}