/*
* hashmap.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 16

// hash function
int hash(int key) { 
    return key % HASHMAP_SIZE; 
}

// initialize a new hashmap
struct HashMap *createHashMap() {
    struct HashMap *map = (struct HashMap *)malloc(sizeof(struct HashMap));
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        map->table[i] = NULL;
    }
  return map;
}

// insert to hashmap
void put(struct HashMap *map, int key, void *value) {
    int index = hash(key);
    // update value
    struct KeyValue *current = map->table[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    // create a new key-value pair
    struct KeyValue *newPair = (struct KeyValue *)malloc(sizeof(struct KeyValue));
    newPair->key = key;
    newPair->value = value;
    newPair->next = map->table[index];
    map->table[index] = newPair;
}

// get value by key
void *get(struct HashMap *map, int key) {
    int index = hash(key);
    struct KeyValue *current = map->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    // key not found
    return NULL;
}

// remove from the hashmap
void removeFromMap(struct HashMap *map, int key) {
    int index = hash(key);

    struct KeyValue *prev = NULL;
    struct KeyValue *current = map->table[index];
    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        if (prev == NULL) {
            map->table[index] = NULL;
        } else {
            prev->next = current->next;
            free(current->value);
            free(current);
        }
    }
}