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