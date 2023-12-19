#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

int isFull(struct Queue* queue) {
    return queue->rear == MAX_SIZE - 1;
}

void enqueue(struct Queue* queue, char* value) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear++;
    queue->items[queue->rear] = value;
}

char* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return "";
    }

    char* removedItem = queue->items[queue->front];
    queue->front++;

    if (queue->front > queue->rear) {
        // Reset queue
        queue->front = -1;
        queue->rear = -1;
    }

    return removedItem;
}