# Task Management Simulation with Circular Stack

## Description

This project aims to simulate a task management system using a Circular Stack data structure. The Circular Stack data structure is used to manage tasks that are done and tasks that are cancelled, ensuring that they are processed in the order they are received.

## Usage

1. Start the task management simulation by running the main program.
2. Users can send commands to the system via stdin, specifying the task and the command (do, undo, redo).
3. The system reads the incoming commands from stdin and processes them accordingly.
4. If the command is "do", the task is pushed onto the `done` stack and the `cancelled` stack is emptied.
5. If the command is "undo", the most recent task is popped from the `done` stack and pushed onto the `cancelled` stack.
6. If the command is "redo", the most recent task is popped from the `cancelled` stack and pushed onto the `done` stack.
7. The system continues to process incoming commands until it receives a "quit" command.

## Benefits

- Using a Circular Stack ensures that tasks are processed in the order they are received, preventing any task from being lost or delayed.
- Stdin provides a simple and standardized way for users to interact with the system.
- The system can handle an arbitrary number of tasks, up to the maximum stack size.

## Example

Here's an example of how to use the task management simulation:

1. Start the program.
2. User sends a "do" command to the system via stdin: `do 1`
3. User sends another "do" command to the system via stdin: `do 2`
4. User sends an "undo" command to the system via stdin: `undo`
5. User sends a "redo" command to the system via stdin: `redo`
6. The system processes the commands, pushing and popping tasks from the `done` and `cancelled` stacks as appropriate.
7. The system continues to process incoming commands until it receives a "quit" command.

## Source Code

**`circular_stack.h`**
```c
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

#endif
```

**`circular_stack.c`**
```c
#include <stdio.h>
#include <stdlib.h>
#include "circular_stack.h"

// Function to create a circular stack
struct CircularStack* createCircularStack() {
    struct CircularStack* stack = (struct CircularStack*)malloc(sizeof(struct CircularStack));
    if (stack == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    stack->capacity = MAX_SIZE;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (stack->array == NULL) {
        printf("Memory allocation failed.\n");
        free(stack);
        return NULL;
    }
    stack->top = -1; // Initialize top index
    stack->size = 0; // Initialize top index
    return stack;
}

// Function to check if the circular stack is empty
int isEmpty(struct CircularStack* stack) {
    return (stack->size == 0);
}

// Function to check if the circular stack is full
int isFull(struct CircularStack* stack) {
    return (stack->size == stack->capacity);
}

// Function to push an element into the circular stack
void push(struct CircularStack* stack, int data) {
    if (isFull(stack)) {
        stack->size--;
    }
    stack->top = (stack->top + 1) % stack->capacity;
    stack->array[stack->top] = data;
    stack->size++;
    printf("%d pushed to the stack.\n", data);
}

// Function to pop an element from the circular stack
int pop(struct CircularStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow. Cannot pop element.\n");
        return -1;
    }
    int popped = stack->array[stack->top];
    stack->top = (stack->top - 1 + stack->capacity) % stack->capacity;
    stack->size--;
    return popped;
}

// Function to display the circular stack
void display(struct CircularStack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Nothing to display.\n");
        return;
    }
    printf("Elements in the circular stack are: ");
    for (int i = stack->top; i > stack->top - stack->size; i--) {
        printf("%d ", stack->array[(i + stack->capacity) % stack->capacity]);
    }
    printf("\n");
}

// Function to empty the circular stack
void emptyStack(struct CircularStack* stack) {
    while (!isEmpty(stack)) {
        int discarded = pop(stack);
        printf("Discarded element: %d\n", discarded);
    }
    printf("Stack is now empty.\n");
}

// Function to free the memory allocated for the circular stack
void freeCircularStack(struct CircularStack* stack) {
    free(stack->array);
    free(stack);
}
```

**`main.c`**
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "circular_stack.h"

int main() {
    struct CircularStack* done = createCircularStack();
    struct CircularStack* cancelled = createCircularStack();

    bool ended = false;
    while (!ended) {
        char* command = (char*)malloc(10 * sizeof(char));
        scanf("%s", command);

        if (!strcmp(command, "do")) {
            int task;
            scanf("%d", &task);
            push(done, task);
            emptyStack(cancelled);
        } else if (!strcmp(command, "undo")) {
            int task = pop(done);
            push(cancelled, task);
        } else if (!strcmp(command, "redo")) {
            int task = pop(cancelled);
            push(done, task);
        } else if (!strcmp(command, "quit")) {
            ended = true;
        } else {
            printf("Invalid command.\n");
        }

        printf("(Done) ");
        display(done);
        printf("(Cancelled) ");
        display(cancelled);
    }

    freeCircularStack(done);
    freeCircularStack(cancelled);
}
```

## Conclusion

By using a Circular Stack data structure and stdin for input, this task management simulation provides an efficient and scalable solution for managing tasks. It ensures that tasks are processed in the order they are received, and allows for undoing and redoing tasks.