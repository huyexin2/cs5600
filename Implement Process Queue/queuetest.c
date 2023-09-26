//
//  queuetest.c
//  
//
//  Created by Yexin Hu on 9/25/23.
//
#include <stdio.h>
#include "queue.h"

int main() {
    // Example usage
    struct queue_t myQueue;
    initializeQueue(&myQueue);

    // Print queue size
    printf("Queue size when initialize queue: %d\n", qsize(&myQueue));

    // Add elements to the queue
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;

    add2q(&myQueue, &num1);
    add2q(&myQueue, &num2);
    add2q(&myQueue, &num3);
    add2q(&myQueue, &num4);
    add2q(&myQueue, &num5);


    // Print the elements from front to rear
    struct Node *current = myQueue.front;
    while (current != NULL) {
        printf("Element: %d\n", *((int *)(current->data)));
        current = current->next;
    }
	printf("Queue size: %d\n", qsize(&myQueue));

    // pop two elements from the queue
	popQ(&myQueue);
	popQ(&myQueue);
	printf("Queue size after pop two elements from the queue: %d\n", qsize(&myQueue));
    return 0;
}
