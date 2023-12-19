#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 10 // Maximum size of the circular stack

struct CircularStack {
    int *array;
    int top;
    int size;
    int capacity;
};

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