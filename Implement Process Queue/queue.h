/*
* queue.h / Implement Process Queue
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 25, 2023
*/

#ifndef queue_h
#define queue_h

#include <stdio.h>

struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
};

// Define the queue_t struct
struct queue_t {
    struct Node *front;
    struct Node *rear;
    int size;
};

// Function to initialize an empty queue
void initializeQueue(struct queue_t *queue);

// Function to add an element to the end of the queue
void add2q(struct queue_t *queue, void *element);

#endif /* queue_h */
