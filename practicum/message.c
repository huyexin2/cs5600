#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "cache.h"

#define CACHE_SIZE 16
#define PAGE_SIZE 1024

struct Cache messageCache;

// Function to create a new message
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


int printMessageFromDB(void *data, int argc, char **argv, char **azColName) {
    printf("Message found in database:\n");
    struct Message* msg = (struct Message*)malloc(sizeof(struct Message));;
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "id") == 0) {
            msg->id = atoi(argv[i]);
        } else if (strcmp(azColName[i], "timeSent") == 0) {
            strcpy(msg->timeSent, argv[i]);
        } else if (strcmp(azColName[i], "sender") == 0) {
            strcpy(msg->sender, argv[i]);
        } else if (strcmp(azColName[i], "receiver") == 0) {
            strcpy(msg->receiver, argv[i]);
        } else if (strcmp(azColName[i], "content") == 0) {
            strcpy(msg->content, argv[i]);
        } else if (strcmp(azColName[i], "isDelivered") == 0) {
            msg->isDelivered = atoi(argv[i]);
        }
    }
    printMessage(msg);
    free(msg);
    return 0;
}

// Function to store a message in the message store and cache
int storeMessage(sqlite3 *db, struct Message *msg) {
    // Store in the database
    char *errMsg;
    char insertQuery[1024];
    snprintf(insertQuery, sizeof(insertQuery), "INSERT INTO Messages (timeSent, sender, receiver, content, isDelivered) VALUES ('%s', '%s', '%s', '%s', %d);",
             msg->timeSent, msg->sender, msg->receiver, msg->content, msg->isDelivered);

    int rc = sqlite3_exec(db, insertQuery, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }

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

// Function to retrieve a message from the message store and cache
int retrieveMessages(sqlite3 *db, int id) {
    struct Message *retrieved_msg;
    struct Message *curMessage;

    char selectQuery[256];
    char updateQuery[256];
    char *errMsg;

    // Check if the message is in the cache
    for (int pageIndex = 0; pageIndex < CACHE_SIZE; pageIndex++) {
        for (int i = 0; i < messageCache.pages.occupied; i++) {
            curMessage = &messageCache.pages.messages[i];
            if (curMessage->id == id) {
                printf("Message found in cache:\n");

                // update isDelivered
                if (curMessage->isDelivered == 0) {
                    snprintf(updateQuery, sizeof(updateQuery), "UPDATE Messages SET isDelivered = 1 WHERE id = %d;", id);
                    int rc = sqlite3_exec(db, updateQuery, printMessageFromDB, curMessage, &errMsg);
                    if (rc != SQLITE_OK) {
                        fprintf(stderr, "SQL error: %s\n", errMsg);
                        sqlite3_free(errMsg);
                        return 1;
                    }
                }
                printMessage(curMessage);   
                leastRecentUse(*curMessage);
                return 0;
            }
        }
    }
    printf("Step1\n");
    // If not found in cache, retrieve from the database, and add it to the cache
    snprintf(selectQuery, sizeof(selectQuery), "SELECT * FROM Messages WHERE id = %d;", id);
    
    int rc = sqlite3_exec(db, selectQuery, printMessageFromDB, retrieved_msg, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        free(curMessage);
        free(retrieved_msg);
        return 1;
    }

    printf("Step2\n");
    printf("Step2.1\n");

    printf("id: %d", retrieved_msg->id);
    if ((retrieved_msg->isDelivered) == 0) {
        printf("Step2.2\n");

        snprintf(updateQuery, sizeof(updateQuery), "UPDATE Messages SET isDelivered = 1 WHERE id = %d;", id);
        rc = sqlite3_exec(db, updateQuery, printMessageFromDB, retrieved_msg, &errMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            free(curMessage);
            free(retrieved_msg);
            return 1;
        }
        printf("Step2.3\n");

        snprintf(selectQuery, sizeof(selectQuery), "SELECT * FROM Messages WHERE id = %d;", id);
        rc = sqlite3_exec(db, selectQuery, printMessageFromDB, retrieved_msg, &errMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            free(curMessage);
            free(retrieved_msg);
            return 1;
        }
    }
    printf("Step3\n");

    if (messageCache.pages.occupied < CACHE_SIZE) {
        messageCache.pages.messages[messageCache.pages.occupied] = *retrieved_msg;
        messageCache.pages.occupied ++;
    } else {
        leastRecentUse(*retrieved_msg);
    }

    free(curMessage);
    free(retrieved_msg);
    return 0;
}


