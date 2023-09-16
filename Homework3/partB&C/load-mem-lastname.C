#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the dynBlock structure.
typedef struct {
    int* array;
    int size;
} dynBlock;

// Allocate a single instance of a dynBlock from the heap and returns a point to the allocated object
dynBlock* allocDynBlock(int size) {
    dynBlock* newBlock = (dynBlock*)malloc(sizeof(dynBlock));
    if (newBlock == NULL) {
        printf("Error: Memory allocation for new dynBlock failed.\n");
    }

    newBlock->size = size;
    newBlock->array = (int*)malloc(size * sizeof(int));
    if (newBlock->array == NULL) {
        printf("Error: Memory allocation for array failed.\n");
        free(newBlock);
        return NULL;
    }
    return newBlock;
}

// Store an array of integers in a dynamic block.
void storeMem2Blk(dynBlock* block, int* array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        block->array[i] = array[i];
    }
}

int main() {
    // Read file
    FILE *file;
    file = fopen("blocks.data", "r");

     if (file == NULL) {
        printf("Error: Cannot open blocks.data.\n");
        return -1;
     }

    char buffer[500];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        int array[500];
        int size = 0;
        char* token = strtok(buffer, " ");
        while (token != NULL) { 
            sscanf(token, "%d", &array[size]);
            size ++;
            token = strtok(NULL, " ");
        }
        dynBlock* block = allocDynBlock(size);
        storeMem2Blk(block, array, size);

        // Print the array stored in the dynBlock
        printf("\n--------dynBlock %p--------\n", block);
        for (int i = 0; i < size; i++) {
            printf("%d ", block->array[i]);
        }
        printf("\n");

        // Free memory
        free(block->array);
        free(block);
    }
    fclose(file);
    return 0;
}