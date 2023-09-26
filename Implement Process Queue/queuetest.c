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

    // Add elements to the queue
    int num1 = 1;
    int num2 = 2;

    add2q(&myQueue, &num1);
    add2q(&myQueue, &num2);

    // Print the elements from front to rear
    struct Node *current = myQueue.front;
    while (current != NULL) {
        printf("Element: %d\n", *((int *)(current->data)));
        current = current->next;
    }

    return 0;
}
