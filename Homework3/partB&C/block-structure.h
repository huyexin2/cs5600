/*
* block-structure.h / Memory Management
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 15, 2023
*/

#ifndef Block_structure_h
#define Block_structure_h

typedef struct block{
    int* array;
    int size;
} dynBlock;

#endif