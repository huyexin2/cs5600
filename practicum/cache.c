/*
* cache.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include "cache.h"
#include "hashmap.h"
#include "message.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CACHE_SIZE 16
#define HASH_MAP_SIZE 16

/*
we use linked list to maintain the order of message. In LRU cache, we need to track the usage
order of the message. Linked list has O(1) for insertion and removal message. 
We also use hashmap to get O(1) to search message in cache.
The alternative approach would be use of list. Since list has O(n) for insertion and removal. We are not consider to use it in this case.
*/

Cache messageCache; // Global cache variable

// create a node
Node *createNode(struct Message *message) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->message = create_msg(message->id, message->timeSent, message->sender, message->receiver, message->content, message->isDelivered);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// remove node
void removeNode(Cache *cache, Node *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        // remove first node
        cache->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        // remove last node
        cache->tail = node->prev;
    }
    cache->occupied--;
}

// add a node to front
void addNodeToFront(Cache *cache, Node *node) {
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head != NULL) {
        cache->head->prev = node;
    }
    cache->head = node;

    // if only one node in the linked list
    if (cache->tail == NULL) {
        cache->tail = node;
    }
    cache->occupied++;
}

void moveNodeToFront(Cache *cache, Node *node) {
    removeNode(cache, node);
    addNodeToFront(cache, node);
}

// remove the last node
void removeLastNode(Cache *cache) {
    if (cache->tail != NULL) {
        removeNode(cache, cache->tail);
    }
}

// get meesage from cache
struct Message *getFromCache(Cache *cache, int messageId) {
    void *node = get(cache->hashmap, messageId);
    if (node != NULL) {
        struct Node *messageNode = (struct Node *)node;
        moveNodeToFront(cache, messageNode);
        return messageNode->message;
    } else {
        return NULL;
    }
}

// random replacement
void randomReplacement(struct Message *msg) {
    // generate a random number
    int randomNumber = rand() % messageCache.occupied - 1;
    Node *cur = messageCache.head;

    // traverse to the random node
    for (int i = 1; i < randomNumber && cur != NULL; i++) {
        cur = cur->next;
    }

    if (cur != NULL) {
        // remove old message from the hashmap
        removeFromMap(messageCache.hashmap, cur->message->id);
        // set current node message to the msg
        cur->message = msg;
        // put new msg in the hashmap
        put(messageCache.hashmap, msg->id, cur);
    } 
}

// add to cache
void addToCache(Cache *cache, struct Message *message) {
    int key = message->id;
    void *node = get(cache->hashmap, key);
    if (node != NULL) {
        struct Node *messageNode = (struct Node *)node;
        messageNode->message = message;
        moveNodeToFront(cache, messageNode);
    }
    if (cache->occupied == CACHE_SIZE) {
        struct Node *lruNode = cache->tail;
        removeNode(cache, cache->tail);
        removeFromMap(cache->hashmap, lruNode->message->id);
    }
    Node *newNode = createNode(message);
    put(cache->hashmap, key, newNode);
    addNodeToFront(cache, newNode);
}

// print cache
void printCache() {
    printf("message in cache:\n");
    Node *current = messageCache.head;
    while (current != NULL) {
        printf("Message ID: %d, Content: %s\n", current->message->id, current->message->content);
        current = current->next;
    }
}