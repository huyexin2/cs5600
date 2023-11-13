#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <time.h>
#include "message.h"
#include "cache.h"

#define CACHE_SIZE 16
#define PAGE_SIZE 1024

int main() {
    
    sqlite3 *db;
    char *errMsg;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    
    //Initialize table
    const char *createTableQuery = "CREATE TABLE IF NOT EXISTS Messages (id INTEGER PRIMARY KEY, timeSent TEXT, sender TEXT, receiver TEXT, content TEXT, isDelivered INT);";

    rc = sqlite3_exec(db, createTableQuery, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    // Initialize the cache
    for (int i = 0; i < CACHE_SIZE; i++) {
        messageCache.pages.occupied = 0;
    }

    // Create and store 1000 new message    
    struct Message *newMsg = NULL;
    for (int i = 1; i < 50; i++ ) {
        newMsg = create_msg(i, "2023-11-10 12:34:56", "Sender1", "Receiver1", "Hello, World!");
        storeMessage(db, newMsg);
    }

    // print cache
    for (int k = 0; k < 16; k++) {
        printf("id: %d\n", messageCache.pages.messages[k].id);
    }

    // Retrieve the message from the cache or database
    for (int j = 1; j < 16; j+=2) {
        retrieveMessages(db, j);
    }
    //retrieveMessages(db, 49);
    //retrieveMessages(db, 48);



    // Reset database to empty
    const char *deleteQuery = "DELETE FROM Messages;";
    rc = sqlite3_exec(db, deleteQuery, 0, 0, &errMsg);

    // Close the SQLite database connection
    sqlite3_close(db);

    // Free allocated memory
    free(newMsg);

    return 0;
}