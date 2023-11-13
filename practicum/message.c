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
#define PAGE_SIZE 1024

struct Cache messageCache;

// create a new message
struct Message* create_msg(int id, const char* timeSent, const char* sender, const char* receiver, const char* content) {
    struct Message* newMessage = (struct Message*)malloc(sizeof(struct Message));
    newMessage->id = id;
    strcpy(newMessage->timeSent, timeSent);
    strcpy(newMessage->sender, sender);
    strcpy(newMessage->receiver, receiver);
    strcpy(newMessage->content, content);
    newMessage->isDelivered = 0;  // Message is not delivered initially
    return newMessage;
}

// store a message in the message store and cache
int storeMessage(sqlite3 *db, struct Message *msg) {
    // Store in the database
    insert(db, msg);

    if (messageCache.pages.occupied < CACHE_SIZE) {
        // Cache is not full, add to the next available slot
        messageCache.pages.messages[messageCache.pages.occupied] = *msg;
        messageCache.pages.occupied++;
    } else {
        // Cache is full, there are two methdology for replacement.
        // Least recent use will replace the first message in cache
        // Ramdom replcaement will pick a ramdom location in page to replace.
        leastRecentUse(*msg);
    }

    return 0;
}

// retrieve a message from the message store and cache
int retrieveMessages(sqlite3 *db, int id) {
    struct Message *msg;

    // check if the message is in the cache
    for (int pageIndex = 0; pageIndex < CACHE_SIZE; pageIndex++) {
        for (int i = 0; i < messageCache.pages.occupied; i++) {
            msg = &messageCache.pages.messages[i];
            if (msg->id == id) {
                printf("Message found in cache:\n");
                printMessage(msg);
                // update isDelivered
                if (msg->isDelivered == 0) {
                    update(db, msg, id);
                    select(db, msg, id);
                }
                leastRecentUse(*msg);
                return 0;
            }
        }
    }
    // If not found in cache, retrieve from the database, and add it to the cache
    select(db, msg, id);

    if (!msg->id) {
        fprintf(stderr, "Cannot find the message by id\n");
		return 1;
    }

    if ((msg->isDelivered) == 0) {
        update(db, msg, id);
        select(db, msg, id);
    }
    printf("Message found in database:\n");
    printMessage(msg);


    if (messageCache.pages.occupied < CACHE_SIZE) {
        messageCache.pages.messages[messageCache.pages.occupied] = *msg;
        messageCache.pages.occupied ++;
    } else {
        leastRecentUse(*msg);
    }
    return 0;
}

// Function to print query results
void printMessage(struct Message *msg) {
    printf("id: %d\n", msg->id);
    printf("timeSent: %s\n", msg->timeSent);
    printf("sender: %s\n", msg->sender);
    printf("receiver: %s\n", msg->receiver);
    printf("content: %s\n", msg->content);
    printf("isDelivered: %d\n", msg->isDelivered);
    printf("\n");
}


