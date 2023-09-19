#include <stdlib.h>
#include <stdio.h>

// Allocate 1MB of stack memory.
void allocateStackMemory() {
    char stackMemory[1 * 1024 * 1024];
    printf("1MB of stack memory is allocated at %p.\n", stackMemory);
}

// Allocate 10MB of heap memory.
char* alloatedHeapMemory() {
    char* heapMemory = (char*)malloc(10 * 1024 * 1024);
    printf("5MB of heap memory is allocated at %p.\n", heapMemory);
    return heapMemory;
}