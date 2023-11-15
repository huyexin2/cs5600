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
#define HASH_MAP_SIZE 16

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    struct Message *message;
} Node;

typedef struct HashMapEntry {
    int key;   // key is message id
    Node *node; // value is pointer to message in the linked list
    Node *next;
} HashMapEntry;

typedef struct Cache {
    Node *head;
    Node *tail;
    int occupied;  // number of occupied slots in the cache
    HashMapEntry *hashMap[HASH_MAP_SIZE]; 
} Cache;

Node *createNode(struct Message *message);
void addHashMapEntry(Cache *cache, int key, Node *node);
Node *findHashMapEntry(Cache *cache, int key);
void removeHashMapEntry(Cache *cache, int key);
void addNodeToFront(Cache *cache, Node *node);
void removeNode(Cache *cache, Node *node);
void moveNodeToFront(Cache *cache, Node *node);
void deleteNode(Node *node);
void leastRecentUse(struct Message *msg);
void randomReplacement(struct Message *msg);
void addToCache(Cache *cache, struct Message *message);
void printCache();

#endif