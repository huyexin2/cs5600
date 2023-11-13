/*
* cache.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>
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

extern struct Cache messageCache;

int leastRecentUse(struct Message msg){
     for (int k = 0; k < messageCache.pages.occupied; k++) {
        if (k == messageCache.pages.occupied - 1) {
            messageCache.pages.messages[k] = msg;
            break;
        }
        messageCache.pages.messages[k] = messageCache.pages.messages[k + 1];
    }         
    return 1;
}

void randomReplacement(struct Message *msg){
    srand(time(NULL));
    // generate a random number between 0 and 15
    int randomNumber = rand() % 16;
    messageCache.pages.messages[randomNumber] = *msg;
}

void printCache() {
    printf("message in cache:\n");
    for (int i = 0; i < 16; i++) {
    printf("id: %d\n", messageCache.pages.messages[i].id);
    }
}

