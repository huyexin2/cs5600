/*
* block-impl.c / Memory Management
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 15, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include "block-structure.h"

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
