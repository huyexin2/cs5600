#include "block-structure.h"

// Allocate a single instance of a dynBlock from the heap and returns a point to the allocated object
dynBlock* allocDynBlock(int size);

// Store an array of integers in a dynamic block.
void storeMem2Blk(dynBlock* block, int* array, int arraySize);