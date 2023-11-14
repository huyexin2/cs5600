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
#include <string.h>
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

unsigned int hash(int key) {
    return key % HASH_MAP_SIZE;
}

Node *createNode(struct Message *message) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    //newNode->message = (Message *)malloc(sizeof(struct Message));
    newNode->message = message; // Copy the contents of the message
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addHashMapEntry(Cache *cache, int key, Node *node) {
    unsigned int index = hash(key);
    HashMapEntry *entry = cache->hashMap[index];

    // check if an entry with the same key already exists
    while (entry != NULL) {
        if (entry->key == key) {
            entry->node = node;  // update the node pointer
            return;
        }
        entry = entry->next;
    }

    // Create a new hash map entry
    HashMapEntry *newEntry = (HashMapEntry *)malloc(sizeof(HashMapEntry));
    newEntry->key = key;
    newEntry->node = node;
    newEntry->next = cache->hashMap[index];  // Insert at the beginning
    cache->hashMap[index] = newEntry;
}

Node *findHashMapEntry(Cache *cache, int key) {
    unsigned int index = hash(key);
    HashMapEntry *entry = cache->hashMap[index];

    while (entry != NULL) {
        if (entry->key == key) {
            return entry->node;  // return the associated node
        }
        entry = entry->next;
    }

    return NULL;  // key not found
}

void removeHashMapEntry(Cache *cache, int key) {
    unsigned int index = hash(key);
    HashMapEntry *entry = cache->hashMap[index];
    HashMapEntry *prevEntry = NULL;

    while (entry != NULL) {
        if (entry->key == key) {
            if (prevEntry == NULL) {
                cache->hashMap[index] = entry->next;  // remove from head
            } else {
                prevEntry->next = entry->next;  // remove from middle or end
            }
            free(entry);  // free the memory of the hash map entry
            return;
        }
        prevEntry = entry;
        entry = entry->next;
    }
}

void addNodeToFront(Cache *cache, Node *node) {
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head != NULL) {
        cache->head->prev = node;
    }
    cache->head = node;

    if (cache->tail == NULL) {
        cache->tail = node;
    }

    cache->occupied++;
}

void removeNode(Cache *cache, Node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        cache->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        cache->tail = node->prev;
    }

    cache->occupied--;
}

void moveNodeToFront(Cache *cache, Node *node) {
    removeNode(cache, node);
    addNodeToFront(cache, node);
}

void deleteNode(Node *node) {
    if (node != NULL) {
        free(node->message);  // Assuming message is dynamically allocated
        free(node);
    }
}
Cache messageCache;  // Global cache variable

void leastRecentUse(struct Message *msg){
    if (messageCache.occupied == CACHE_SIZE) {
        removeHashMapEntry(&messageCache, messageCache.tail->message->id);
        removeNode(&messageCache, messageCache.tail);
    }
    Node *newNode = createNode(msg);
    addNodeToFront(&messageCache, newNode);
    addHashMapEntry(&messageCache, newNode->message->id, newNode);

}

void randomReplacement(struct Message *msg) {

    //srand(time(NULL));

    // Generate a random number within the range of occupied slots
    int randomNumber = rand() % messageCache.occupied - 1 ;
    Node *cur = messageCache.head;

    // Traverse to the random node
    for (int i = 1; i < randomNumber && cur != NULL; i++) {
        cur = cur->next;
    }

    // Replace the message in the found node
    if (cur != NULL) {
        // Remove the old message entry from the hash map
        removeHashMapEntry(&messageCache, cur->message->id);

        // Free the old message
        free(cur->message->content);

        // Create a new message and assign it to the node
        cur->message->id = &msg->id;
        //cur->message->content = msg->content;

        // Add the new message entry to the hash map
        addHashMapEntry(&messageCache, msg->id, cur);
    }
}

void addToCache(Cache *cache, struct Message *message) {
    Node *newNode = createNode(&message);
    if (messageCache.occupied < CACHE_SIZE) {
        addNodeToFront(&messageCache, newNode);
        addHashMapEntry(&messageCache, message->id, newNode);
    } else {
        leastRecentUse(message);
    }
}

void printCache() {
    printf("message in cache:\n");
    Node *current = messageCache.head;
    while (current != NULL) {
        printf("Message ID: %d, Content: %s\n", current->message->id, current->message->content);
        current = current->next;
    }
}