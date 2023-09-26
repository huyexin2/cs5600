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

//Function to remove and return the process with the highest priority in the queue.
struct process_t* rmProcess(struct queue_t* queue);

// Function to remove an element at front of the queue.
int popQ(struct queue_t *queue);

// Function to return the number of elements in the queue.
int qsize(struct queue_t *queue);

#endif /* queue_h */
