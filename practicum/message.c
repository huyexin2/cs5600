/*
* message.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "query.h"
#include "cache.h"

#define CACHE_SIZE 16

struct Cache messageCache;

// create a new message
struct Message* create_msg(int id, const char* timeSent, const char* sender, const char* receiver, const char* content) {
    struct Message* newMessage = (struct Message*)malloc(sizeof(struct Message));
    newMessage->id = id;
    strcpy(newMessage->timeSent, timeSent);
    strcpy(newMessage->sender, sender);
    strcpy(newMessage->receiver, receiver);
    strcpy(newMessage->content, content);
    newMessage->isDelivered = 0;  // message is not delivered initially
    return newMessage;
}

// store a message in the message store and cache
int storeMessage(sqlite3 *db, struct Message *msg) {
    // store in the database
    insert(db, msg);
    // store in cache
    addToCache(&messageCache, msg);
    return 0;
}


// retrieve a message from the message store and cache
int retrieveMessages(sqlite3 *db, int id) {
    struct Message *msg = NULL;

    // check if the message is in the cache
    Node *node = findHashMapEntry(&messageCache, id);

    // cannot find message in cache
    if (node == NULL) {
        select(db, msg, id);

        if ((msg->isDelivered) == 0) {
            update(db, id);
            select(db, msg, id);
        }
        printf("Message found in database:\n");
        printMessage(msg);
        addToCache(&messageCache, msg);
        return 0;
    }

    if (node->message->id == id) {
        msg = node->message;
        printf("Message found in cache:\n");
        // update isDelivered
        if (node->message->isDelivered == 0) {
            update(db, id);
            select(db, msg, id);
            printMessage(msg);
        }
        addToCache(&messageCache, msg);
        return 0;
    }

    // if not found in cache, retrieve from the database, and add it to the cache
    
}

// print query results
void printMessage(struct Message *msg) {
    printf("id: %d\n", msg->id);
    printf("timeSent: %s\n", msg->timeSent);
    printf("sender: %s\n", msg->sender);
    printf("receiver: %s\n", msg->receiver);
    printf("content: %s\n", msg->content);
    printf("isDelivered: %d\n", msg->isDelivered);
    printf("\n");
}

// update message
struct Message updateMessage(sqlite3 *db, int id) {
    struct Message *msg = NULL;
    if (msg->isDelivered == 0) {
        update(db, id);
        select(db, msg, id);
        printMessage(msg);
    }
    return *msg;
}

