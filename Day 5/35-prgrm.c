#include <stdio.h>

#define MAX_BLOCKS 100
#define BLOCK_SIZE 1024

typedef struct {
    int index[MAX_BLOCKS];
} IndexBlock;

void initializeIndexBlock(IndexBlock *indexBlock) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        indexBlock->index[i] = -1; 
    }
}

void allocateBlock(IndexBlock *indexBlock, int fileBlockNumber, int diskBlockNumber) {
    indexBlock->index[fileBlockNumber] = diskBlockNumber;
}

int main() {
    IndexBlock indexBlock;
    initializeIndexBlock(&indexBlock);

    allocateBlock(&indexBlock, 0, 5);  
    allocateBlock(&indexBlock, 1, 8);   
    allocateBlock(&indexBlock, 2, 12);  

    printf("File Allocation Table:\n");
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (indexBlock.index[i] != -1) {
            printf("Block %d -> Disk Block %d\n", i, indexBlock.index[i]);
        }
    }

    return 0;
}