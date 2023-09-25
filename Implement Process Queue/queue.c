/*
* queue.c / Implement Process Queue
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 25, 2023
*/

#include <stdio.h>

// Define the process_t struct
struct process_t {
    int identifier;
    char *name;
    long cumulativeRuntime;
    int priority;
};

struct Node {
    void *data;
    struct Node *next;
};

// Define the queue_t struct
struct queue_t {
    struct Node *front;
    struct Node *rear;
    int size;
};
