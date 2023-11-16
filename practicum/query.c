/*
* query.c / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include "query.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

// insert message
int insert(sqlite3 *db, struct Message *msg) {
    char *errMsg;
    char insertQuery[1024];

    snprintf(insertQuery, sizeof(insertQuery), "INSERT INTO Messages (id, timeSent, sender, receiver, content, isDelivered) VALUES ('%d', '%s', '%s', '%s', '%s', '%d');",
        msg->id, msg->timeSent, msg->sender, msg->receiver, msg->content,
        msg->isDelivered);

    int rc = sqlite3_exec(db, insertQuery, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}

// callback function
int callback(void *data, int argc, char **argv, char **azColName) {
    struct Message *msg = (struct Message *)data;
    msg->id = atoi(argv[0]);
    strncpy(msg->timeSent, argv[1], sizeof(msg->timeSent));
    strncpy(msg->sender, argv[2], sizeof(msg->sender));
    strncpy(msg->receiver, argv[3], sizeof(msg->receiver));
    strncpy(msg->content, argv[4], sizeof(msg->content));
    msg->isDelivered = atoi(argv[5]);
    return 0;
}

// select message
int selectMessageById(sqlite3 *db, struct Message *msg, int id) {
    char *errMsg;
    char selectQuery[256];

    sprintf(selectQuery, "SELECT * FROM Messages WHERE id = %d;", id);

    int rc = sqlite3_exec(db, selectQuery, callback, msg, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }
    return 0;
}

// update by id
int update(sqlite3 *db, int id) {
    char *errMsg;
    char updateQuery[256];

    sprintf(updateQuery, "UPDATE Messages SET isDelivered = 1 WHERE id = %d;", id);
    int rc = sqlite3_exec(db, updateQuery, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 1;
    }

    return 0;
}

