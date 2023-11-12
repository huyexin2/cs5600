#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>

#define CACHE_SIZE 16
#define PAGE_SIZE 1024

struct Message {
    int id;
    char timeSent[20];
    char sender[100];
    char receiver[100];
    char content[500];
    int isDelivered;
};

struct Page {
    struct Message messages[CACHE_SIZE];
    int occupied; // Number of occupied slots in the page
};

struct Cache {
    struct Page pages;
};

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
    struct Message msg;
    for (int i = 0; i < argc; i++) {
        if (strcmp(azColName[i], "id") == 0) {
            msg.id = atoi(argv[i]);
        } else if (strcmp(azColName[i], "timeSent") == 0) {
            strcpy(msg.timeSent, argv[i]);
        } else if (strcmp(azColName[i], "sender") == 0) {
            strcpy(msg.sender, argv[i]);
        } else if (strcmp(azColName[i], "receiver") == 0) {
            strcpy(msg.receiver, argv[i]);
        } else if (strcmp(azColName[i], "content") == 0) {
            strcpy(msg.content, argv[i]);
        } else if (strcmp(azColName[i], "isDelivered") == 0) {
            msg.isDelivered = atoi(argv[i]);
        }
    }
    printMessage(&msg);
    return 0;
}

int leastRecentUse(struct Message *msg){
    messageCache.pages.messages[0] = *msg;
}

int randomReplacement(struct Message *msg){
    srand(time(NULL));

    // Generate a random number between 0 and 15
    int randomNumber = rand() % 16;
    messageCache.pages.messages[0] = *msg;
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

    // Store in the cache
    int pageIndex = messageCache.pages.occupied / CACHE_SIZE;

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
    // Check if the message is in the cache
    for (int pageIndex = 0; pageIndex < CACHE_SIZE; pageIndex++) {
        for (int i = 0; i < messageCache.pages.occupied; i++) {
            if (messageCache.pages.messages[i].id == id) {
                printf("Message found in cache:\n");
                printMessage(&messageCache.pages.messages[i]);
                return 0;
            }
        }
    }

    // If not found in cache, retrieve from the database
    char selectQuery[256];
    char *errMsg;
    snprintf(selectQuery, sizeof(selectQuery), "SELECT * FROM Messages WHERE id = %d;", id);

    int rc = sqlite3_exec(db, selectQuery, printMessage, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }

    return 0;
}

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

    // Create and store a new message
    struct Message *newMsg = create_msg(1, "2023-11-10 12:34:56", "Sender1", "Receiver1", "Hello, World!");
    storeMessage(db, newMsg);

    // Retrieve the message from the cache or database
    retrieveMessages(db, 1);

    // Close the SQLite database connection
    sqlite3_close(db);

    // Free allocated memory
    free(newMsg);

    return 0;
}
