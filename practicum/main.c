/*
* main.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include "cache.h"
#include "message.h"
#include "hashmap.h"
#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CACHE_SIZE 16
#define HASH_MAP_SIZE 16

// counter 
float dbCounter = 0;
float cacheCounter = 0;

int main() {
    srand(time(NULL));
    sqlite3 *db;
    char *errMsg;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    // initialize table
    const char *createTableQuery = "CREATE TABLE IF NOT EXISTS Messages (id INTEGER PRIMARY KEY, timeSent TEXT, sender TEXT, receiver TEXT, content TEXT, isDelivered INT);";

    rc = sqlite3_exec(db, createTableQuery, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // initialize cache
    messageCache.head = NULL;
    messageCache.tail = NULL;
    messageCache.hashmap = createHashMap();
    messageCache.occupied = 0;

    // Create and store 1000 new message
    struct Message *newMsg = NULL;
    for (int i = 1; i < 1001; i++) {
        newMsg = create_msg(i, "2023-11-10 12:34:56", "Sender1", "Receiver1", "Hello, World!", 0);
        storeMessage(db, newMsg);
    }

    // print cache
    printCache();

    // retrieve message from cache
    for (int i = 1; i < 1000; i++) {
        // generate a random number between 0 and 15
        int randomNumber = rand() % 1000;
        retrieveMessages(db, randomNumber);
    }

    printf("number of cache hits per 1000 random message accesses: %f\n", cacheCounter);
    printf("number of cache misses per 1000 random message accesses: %f\n", dbCounter);
    cacheCounter = cacheCounter/1000;
    printf("cache hit ratio per 1000 random message accesses : %f\n", cacheCounter);    

    // print cache
    // printCache();

    // reset database to empty
    const char *deleteQuery = "DROP TABLE Messages;";
    rc = sqlite3_exec(db, deleteQuery, 0, 0, &errMsg);

    // close the SQLite database connection
    sqlite3_close(db);

    // free allocated memory
    free(newMsg);

    return 0;
}