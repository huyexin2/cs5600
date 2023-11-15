/*
* main.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <time.h>
#include "message.h"
#include "cache.h"

#define CACHE_SIZE 16
#define HASH_MAP_SIZE 16

int main() {
    srand(time(NULL));
    sqlite3 *db;
    char *errMsg;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    
    //initialize table
    const char *createTableQuery = "CREATE TABLE IF NOT EXISTS Messages (id INTEGER PRIMARY KEY, timeSent TEXT, sender TEXT, receiver TEXT, content TEXT, isDelivered INT);";

    rc = sqlite3_exec(db, createTableQuery, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // initialize the cache
    messageCache.head = NULL;
    messageCache.tail = NULL;
    messageCache.occupied = 0;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        messageCache.hashMap[i] = NULL;
    }

    // Create and store 1000 new message    
    struct Message *newMsg = NULL;
    for (int i = 1; i < 50; i++ ) {
        newMsg = create_msg(i, "2023-11-10 12:34:56", "Sender1", "Receiver1", "Hello, World!");
        storeMessage(db, newMsg);
    }

    // print cache
    printCache();

    // retrieve message from cache
    retrieveMessages(db, 48);
    retrieveMessages(db, 49);

    // retrieve message from database
    retrieveMessages(db,10);
    retrieveMessages(db,11);

    // print cache
    printCache();

    // reset database to empty
    const char *deleteQuery = "DELETE FROM Messages;";
    rc = sqlite3_exec(db, deleteQuery, 0, 0, &errMsg);

    // close the SQLite database connection
    sqlite3_close(db);

    // free allocated memory
    free(newMsg);

    return 0;
}