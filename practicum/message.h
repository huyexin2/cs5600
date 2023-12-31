/*
* message.h / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <sqlite3.h>
#include <string.h>

extern struct Cache messageCache;

// message structure
struct Message {
    int id;
    char timeSent[20];
    char sender[100];
    char receiver[100];
    char content[500];
    int isDelivered;
};

// create message
struct Message* create_msg(int id, const char* timeSent, const char* sender, const char* receiver, const char* content);
// store message
int storeMessage(sqlite3 *db, struct Message *msg);
// retrieve message by id
int retrieveMessages(sqlite3 *db, int id);
// print message
void printMessage(struct Message *msg);
// print message from database
int printMessageFromDB(void *data, int argc, char **argv, char **azColName);

#endif // MESSAGE_H
