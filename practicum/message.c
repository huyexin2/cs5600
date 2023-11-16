/*
* message.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include "message.h"
#include "cache.h"
#include "query.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 16

extern struct Cache messageCache;
extern float dbCounter;
extern float cacheCounter;

// create a new message
struct Message *create_msg(int id, const char *timeSent, const char *sender, const char *receiver, const char *content, int isDelivered) {
    struct Message *newMessage = (struct Message *)malloc(sizeof(struct Message));
    newMessage->id = id;
    strcpy(newMessage->timeSent, timeSent);
    strcpy(newMessage->sender, sender);
    strcpy(newMessage->receiver, receiver);
    strcpy(newMessage->content, content);
    newMessage->isDelivered = isDelivered; // message is not delivered initially
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
    // check if the message is in the cache
    struct Message *msg = getFromCache(&messageCache, id);

    // if not found in cache, retrieve from the database, and add it to the cache
    if (msg == NULL) {
        struct Message data;
        printf("Message %d not found in cache:\n", id);
        selectMessageById(db, &data, id);
        dbCounter++;

        // update isDelivered from 0 to 1
        if (data.isDelivered == 0) {
            update(db, id);
            selectMessageById(db, &data, id);
            //printMessage(&data);
        }

        // update cache
        addToCache(&messageCache, &data);
        printMessage(&data);
        return 0;

    } else {
        // found in cache
        cacheCounter++;
        printf("Message found in cache:\n");
        printMessage(msg);
        return 0;
    }
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

