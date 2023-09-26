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

// Function to initialize an empty queue
void initializeQueue(struct queue_t *queue) {
    queue->front =  NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Function to add an element to the end of the queue
void add2q(struct queue_t *queue, void *element) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory for node.\n");
        exit(1);
    }

    newNode->data = element;
    newNode->next = NULL;
    
    // Case when queue is empty
    if (queue->rear == NULL) {
        newNode->prev = NULL;
        queue->front = newNode;
    }
    // Case when queue is not empty
    else {
        newNode->prev = queue->rear;
        queue->rear->next = newNode;
    }

    queue->rear = newNode;
    queue->size++;
}
