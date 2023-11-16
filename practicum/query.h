/*
* query.h / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#ifndef QUERY_H
#define QUERY_H

#include "message.h"
#include <sqlite3.h>

// update by id
int update(sqlite3 *db, int id);
// insert message
int insert(sqlite3 *db, struct Message *msg);
// select message
int selectMessageById(sqlite3 *db, struct Message *msg, int id);

#endif