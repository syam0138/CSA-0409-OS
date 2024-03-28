#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024

typedef struct Block {
    char data[BLOCK_SIZE];
    struct Block* next;
} Block;

typedef struct {
    Block* firstBlock;
    Block* lastBlock;
} File;

void initializeFile(File* file) {
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

void addBlock(File* file, int blockNumber) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    if (newBlock == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newBlock->next = NULL;

    if (file->lastBlock == NULL) {
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }

    printf("Block %d added to the file.\n", blockNumber);
}

void printFileBlocks(File* file) {
    Block* currentBlock = file->firstBlock;

    while (currentBlock != NULL) {
        printf("Block: %p -> Next: %p\n", currentBlock, currentBlock->next);
        currentBlock = currentBlock->next;
    }
}

void deallocateFile(File* file) {
    Block* currentBlock = file->firstBlock;
    Block* nextBlock;

    while (currentBlock != NULL) {
        nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

int main() {
    File myFile;
    initializeFile(&myFile);

    addBlock(&myFile, 1);
    addBlock(&myFile, 2);
    addBlock(&myFile, 3);

    printf("File Blocks:\n");
    printFileBlocks(&myFile);

    deallocateFile(&myFile);

    return 0;
}