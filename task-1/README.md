# Task 1: Guessing Game

## Statement

Write an application for a number guessing game implementing this workflow:

* The application chooses a random number between 10 and 250 (inclusive)
* The user tries to guess the number in 10 trials
* The application tells the user whether their guess is less, greater or equal to the chosen number
* If the user runs out of trials, they get a failure message
* If the user gets the correct number, the game ends
* Before the application closes, the previous guesses of the user are printed

## Specifications

* The application includes a `get_random_int` function which returns a random number between 10 and 250 (inclusive)
* The application includes a `validate_user_input` function which takes the user guess and the chosen answer and compares them. It returns `true` if the answer is correct, otherwise it prints a message to the user describing whether the guess is more or less than the answer and returns `false`
* The application includes both `print_win` and `print_lose` functions which print the result of the game to the console

## Code
```c
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
```

## Runtime
```
Enter your guess
-> 60
That's too small
Enter your guess
-> 110
That's too small
Enter your guess
-> 180
That's too small
Enter your guess
-> 200
That's too small
Enter your guess
-> 230
That's too big
Enter your guess
-> 210
That's too small
Enter your guess
-> 222
That's too small
Enter your guess
-> 226
That's too big
Enter your guess
-> 224
WIN ... Siuuuuu
Guess #1: 60
Guess #2: 110
Guess #3: 180
Guess #4: 200
Guess #5: 230
Guess #6: 210
Guess #7: 222
Guess #8: 226
Guess #9: 224
```