#include <stdio.h>
#include <stdlib.h>

// Define the dynBlock structure.
typedef struct {
    int* array;
    size_t size;
} dynBlock;

// Allocate a single instance of a dynBlock from the heap and returns a point to the allocated object
dynBlock* allocDynBlock() {
    dynBlock* block = (dynBlock*)malloc(sizeof(dynBlock));
    return block;
}

// Store an array of integers in a dynamic block.
void storeMem2Blk(dynBlock* block, int* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        block->array[i] = array[i];
    }
}

int main() {
    // Read file
    FILE *file;
    file = fopen("blocks.data", "r");
     if (file != NULL) {
        char buffer[100];
        while(fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Error: Cannot open the file.\n");
        return -1;
    }
    return 0;
}