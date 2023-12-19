#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h> // Include pthread.h
#include <windows.h> // Include windows.h

#define MAX_SIZE 100

typedef void (*Callback)(void);

typedef enum {
    blue,
    red,
    green,
    reset
} color;


void set_color(color choosed_color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (choosed_color) {
        case blue:
            // Set text color to blue
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            break;
        case red:
            // Set text color to red
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            break;
        case green:
            // Set text color to green
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            break;
        case reset:
            // Reset text color
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
    }
}

struct Queue {
    char* items[MAX_SIZE];
    int front;
    int rear;
};


struct Queue* queue;
bool ended;

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

void* asyncTask(void* arg) { // Modify asyncTask to accept and return void*
    Callback callback = (Callback)arg;
    while (!ended || !isEmpty(queue)) {
        sleep(5);
        if (!isEmpty(queue)) {
            callback();
        }
    }
    return NULL;
}

void handleRequests() {
    char* request = dequeue(queue);
    set_color(green);
    printf("Handling request %s\n", request);
    set_color(red);
}

void listenRequestsMessage() {
    set_color(blue);
    printf("Listening for requests...\n");
    set_color(red);
}


int main() {
    queue = createQueue();
    ended = false;

    printf("Web server started.\n");
    printf("Type 'end' to stop the server.\n");

    pthread_t thread_id; // Declare pthread_t variable
    pthread_create(&thread_id, NULL, asyncTask, handleRequests); // Create a new thread that runs asyncTask

    while (!ended) {
        listenRequestsMessage();
        char* request = (char*)malloc(sizeof(char) * 100);
        scanf("%s", request);

        if (strcmp(request, "end") == 0) {
            ended = true;
        } else {
            enqueue(queue, request);
        }
    }

    pthread_join(thread_id, NULL); // Wait for the worker thread to finish

    return 0;
}