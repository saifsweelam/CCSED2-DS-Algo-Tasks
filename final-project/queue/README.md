# Web Server Simulation with Queue

## Description

This project aims to simulate a web server using a Queue data structure, stdin/stdout for input/output, and multi-threading for concurrent processing. The Queue data structure is used to manage incoming requests from clients, ensuring that they are processed in the order they are received. 

## Usage

1. Start the web server simulation by running the main program.
2. Clients can send requests to the server via stdin, specifying the requested resource and any additional parameters.
3. The server reads the incoming requests from stdin and enqueues them into the request queue.
4. A worker thread is created to process the requests.
5. The worker thread dequeues a request from the queue, simulates server work for 5 seconds, and sends the response to stdout.
6. The server continues to process incoming requests until it receives a termination signal.

## Benefits

- Using a Queue ensures that requests are processed in the order they are received, preventing any request from being starved or delayed.
- Stdin/stdout provides a simple and standardized way for clients to communicate with the server.
- Multi-threading allows for concurrent processing of requests, improving the server's performance and responsiveness.

## Example

Here's an example of how to use the web server simulation:

1. Start the server program.
2. Client 1 sends a request to the server via stdin: `getUsers`
3. Client 2 sends a request to the server via stdin: `createUser`
4. The server enqueues both requests into the request queue.
5. Worker threads process the requests concurrently.
6. The server sends the response for Client 1's request to stdout: `Handling request getUsers`
7. The server sends the response for Client 2's request to stdout: `Handling request createUser`
8. The server continues to process incoming requests until it receives a termination signal.

## Source Code

**`colors.h`**
```c
#ifndef COLOR_H
#define COLOR_H

typedef enum {
    blue,
    red,
    green,
    reset
} color;

void set_color(color choosed_color);

#endif
```

**`colors.c`**
```c
#include <windows.h>
#include "colors.h"

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
```

**`queue.h`**
```c
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
```

**`queue.c`**
```c
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
```

**`main.c`**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "queue.h"
#include "colors.h"

typedef void (*Callback)(void);

struct Queue* queue;
bool ended;

void* asyncTask(void* arg) {
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
```

## Conclusion

By using a Queue data structure, stdin/stdout for input/output, and multi-threading, this web server simulation provides an efficient and scalable solution for handling incoming requests from clients. It ensures that requests are processed in the order they are received, while allowing for concurrent processing to improve performance.