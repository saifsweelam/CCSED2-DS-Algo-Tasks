#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100

struct Queue {
    char* items[MAX_SIZE];
    int front;
    int rear;
};

struct Queue* createQueue();
int isEmpty(struct Queue* queue);
int isFull(struct Queue* queue);
void enqueue(struct Queue* queue, char* value);
char* dequeue(struct Queue* queue);

#endif