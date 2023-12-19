#ifndef CIRCULAR_STACK_H
#define CIRCULAR_STACK_H

#define MAX_SIZE 10 // Maximum size of the circular stack

struct CircularStack {
    int *array;
    int top;
    int size;
    int capacity;
};

struct CircularStack* createCircularStack();
int isEmpty(struct CircularStack* stack);
int isFull(struct CircularStack* stack);
void push(struct CircularStack* stack, int data);
int pop(struct CircularStack* stack);
void display(struct CircularStack* stack);
void emptyStack(struct CircularStack* stack);
void freeCircularStack(struct CircularStack* stack);

#endif // CIRCULAR_STACK_H