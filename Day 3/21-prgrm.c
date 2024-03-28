#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct MemoryBlock {
    int size;
    int allocated;
};
void worstFit(struct MemoryBlock memory[], int n, int processSize) {
    int worstFitIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (worstFitIndex == -1 || memory[i].size > memory[worstFitIndex].size) {
                worstFitIndex = i;
            }
        }
    }
    if (worstFitIndex != -1) { 
        memory[worstFitIndex].allocated = 1;
        printf("Memory allocated for process of size %d at block %d\n", processSize, worstFitIndex);
    } else {
        
        printf("Insufficient memory to allocate for process of size %d\n", processSize);
    }
}
void displayMemory(struct MemoryBlock memory[], int n) {
    printf("\nMemory Status:\n");
    for (int i = 0; i < n; i++) {
        printf("Block %d: Size = %d, Allocated = %s\n", i, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
    printf("\n");
}
int main() {
    int n; 
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);
    struct MemoryBlock memory[MAX_BLOCKS];
    for (int i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i);
        scanf("%d", &memory[i].size);
        memory[i].allocated = 0; 
    }
    int processSize;
    while (1) {
        printf("Enter the size of the process to allocate (or -1 to exit): ");
        scanf("%d", &processSize);
        if (processSize == -1) {
            break;
        }
        worstFit(memory, n, processSize);
        displayMemory(memory, n);
    }
    return 0;
}