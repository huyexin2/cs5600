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

int leastRecentUse(struct Message msg);

int randomReplacement(struct Message *msg);

