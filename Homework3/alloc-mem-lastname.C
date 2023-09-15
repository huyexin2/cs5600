#include <stdio.h>


static byte[] static_memory[5 * 1024];

void main() {
    
    byte[] stack_memory[1024];
    
    byte[] heap_memory[10 * 1024];

    if (heap_memory == NULL) {
        printf("Error: Failed to allocate memory from the heap.\n");
        exit(0);
    }

    printf("Heap memory is allocated at %p.\n", heap_memory);
    printf("Stack memory is allocated at %p.\n", stack_memory);
    printf("Static memory is allocated at %p.\n", static_memory);

    free(heap_memory);
    printf("Heap memory is free.\n");

    printf("Heap memory is allocated at %p.\n", heap_memory);
}