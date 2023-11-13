/*
* query.h / Practicum I
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Nov 14, 2023
*/

#include <sqlite3.h>
#include "message.h"

#ifndef QUERY_H
#define QUERY_H

// update by id
int update(sqlite3 *db, struct Message *msg, int id);
// insert message
int insert(sqlite3 *db, struct Message *msg);
// select message
int select(sqlite3 *db, struct Message *msg, int id);

#endif
