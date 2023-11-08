#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int get_random_num() {
    return rand() % 241 + 10;
}

bool validate_user_input(int guess, int answer) {
    if (guess == answer) return true;
    else if (guess < answer) {
        printf("That's too small\n");
    } else {
        printf("That's too big\n");
    }
    return false;
}

void print_win() {
    printf("WIN ... Siuuuuu\n");
}

void print_lose() {
    printf("Loser :P\n");
}

int main() {
    srand(time(NULL));

    int answer = get_random_num(), trials = 0, guesses[10];
    bool winning = false;
    while (trials < 10) {
        trials++;
        printf("Enter your guess\n-> ");
        scanf("%d", &guesses[trials-1]);
        if (validate_user_input(guesses[trials-1], answer)) {
            winning = true;
            print_win();
            break;
        }
    }
    if (!winning) print_lose();
    for (int i = 0; i < trials; i++) {
        printf("Guess #%d: %d\n", i+1, guesses[i]);
    }
}