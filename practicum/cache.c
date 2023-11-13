#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

struct Cache messageCache;

int leastRecentUse(struct Message msg){
    messageCache.pages.messages[0] = msg;
    return 1;
}

int randomReplacement(struct Message *msg){
    srand(time(NULL));

    // Generate a random number between 0 and 15
    int randomNumber = rand() % 16;
    messageCache.pages.messages[randomNumber] = *msg;
}