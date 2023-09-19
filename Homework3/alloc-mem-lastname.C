/*
* alloc-mem-lastname.c / Memory Management
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 15, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include "alloc-mem.h"

// Allocate 5MB of static memory.
static char staticMemory[5 * 1024 * 1024];

int main() {

    printf("\n----------Stack----------\n");
    allocateStackMemory();
    printf("Stack memory is freed when the function exists.\n\n");
    
    printf("----------Heap----------\n");
    char* heapMemory = alloatedHeapMemory();
    if (heapMemory == NULL) {
        printf("Error: Failed to allocate memory from the heap.\n\n");
        return -1;
    } else {
        free(heapMemory);
        printf("Heap memory is freed manually.\n\n");
    }

    printf("----------Static Segment----------\n");
    printf("Static memory is allocated at %p and is freed when the program terminates.\n\n", staticMemory);
    
    return 0;
}