/*
* cache.h / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#ifndef CACHE_H  
#define CACHE_H 

#include "message.h"

#define CACHE_SIZE 16
#define PAGE_SIZE 1024

struct Page {
    struct Message messages[CACHE_SIZE];
    int occupied; // Number of occupied slots in the page
};

struct Cache {
    struct Page pages;
};

int leastRecentUse(struct Message msg);
void randomReplacement(struct Message *msg);
void printCache();

#endif
