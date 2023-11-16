/*
* hashmap.h / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#ifndef HASHMAP_H
#define HASHMAP_H

#include "message.h"

#define HASHMAP_SIZE 16

// key-value pair structure
struct KeyValue {
    int key;
    void *value; // pointer to the message
    struct KeyValue *next;
};

// hashmap structure
struct HashMap {
    struct KeyValue *table[HASHMAP_SIZE];
};

// initialize a new hashmap
struct HashMap *createHashMap();
// insert to hashmap
void put(struct HashMap *map, int key, void *value);
// get value by key
void *get(struct HashMap *map, int key);
// remove from the hashmap
void removeFromMap(struct HashMap *map, int key);

#endif