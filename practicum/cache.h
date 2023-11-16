/*
* cache.h / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#ifndef CACHE_H
#define CACHE_H

#include "hashmap.h"
#include "message.h"

#define CACHE_SIZE 16
#define HASH_MAP_SIZE 16

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    struct Message *message;
} Node;

typedef struct Cache {
    Node *head;
    Node *tail;
    struct HashMap *hashmap;
    int occupied; // number of occupied slots in the cache
} Cache;

void randomReplacement(struct Message *msg);
struct Message *getFromCache(Cache *cache, int messageId);
void addToCache(Cache *cache, struct Message *message);
void printCache();

#endif