/*
* load-mem-lastname.c / Memory Management
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 15, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block-impl.h"
#include "block-structure.h"

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