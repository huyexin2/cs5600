/*
* alloc-mem.c / Memory Management
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 15, 2023
*/

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