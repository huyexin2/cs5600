/*
* queue.c / Implement Process Queue
*
* Yexin Hu, Yi Hsin Wen / CS5600 / Northeastern University
* Fall 2023 / Sep 25, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define the process_t struct
typedef struct {
    int identifier;
    char *name;
    long cumulativeRuntime;
    int priority;
} process_t;

typedef struct {
    void *data;
    struct Node *next;
} Node;

// Define the queue_t struct
typedef struct {
    struct Node *front;
    struct Node *rear;
    int size;
} queue_t;

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

// Remove and return the data within the element at the front of the queue.
int popQ(struct queue_t *queue) {
	if (!queue->front) {
		return -1;
	}
	struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
	tmp = queue->front;
	int *data = tmp->data;
	queue->front = tmp->next;
	
	if (queue->front) {
        queue->front->prev = NULL;
    } else {
        queue->rear = NULL;
    }
    free(tmp);
    queue->size--;
    return *data;	
}

// Return the number of elements in the queue; 0 if the queue is empty.
int qsize(struct queue_t *queue) {
	if (!queue) {
		return 0;
	}
	return queue->size;
}

//Remove and return the process with the highest priority in the queue.
struct process_t* rmProcess(struct queue_t *queue) {
	struct Node *current = queue->front;
	struct Node *highestPriority = current;
	while (current) {
        process_t *process = (process_t*) current->data;
        process_t *highestPriorityProcess = (process_t*) highestPriority->data;

        if (process->priority > highestPriorityProcess->priority) {
            highestPriority = current;
        }
        current = current->next;
    }
	if (!highestPriority) {
		return NULL;
	}
	
	if (highestPriority->prev) {
        highestPriority->prev->next = highestPriority->next;
    } else {
		// highest priority node is the first element in the queue.
        queue->front = highestPriority->next;
    }
    
    if (highestPriority->next) {
        highestPriority->next->prev = highestPriority->prev;
    } else {
		// highest priority node is the last element in the queue.
        queue->rear = highestPriority->prev;
    }
    process_t *highestPriorityProcess = (process_t*) highestPriority->data;
    free(highestPriority);
    queue->size--;
    return highestPriorityProcess;
}