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