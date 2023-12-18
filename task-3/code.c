#include <stdio.h>
#include <stdbool.h>

void init_grid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int k = (i * 3) + j;
            grid[i][j] = k + '1';
        }
    }
}

void print_grid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");
    }
}

char check_winner(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) return grid[i][0];
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) return grid[0][i];
    }
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return grid[0][0];
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[0][2]) return grid[0][2];
    return ' ';
}

void move(char grid[3][3], char player) {
    int pos;
    printf("Player %c's move:\n", player);
    scanf("%d", &pos);
    pos--;
    int x = pos / 3;
    int y = pos % 3;
    if (grid[x][y] == 'X' || grid[x][y] == 'O') {
        printf("Invalid move\n");
        move(grid, player);
    }
    grid[x][y] = player;
}

bool check_full_grid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != 'X' && grid[i][j] != 'O') return false;
        }
    }
    return true;
}

int main() {
    char grid[3][3];
    init_grid(grid);
    char winner = ' ';
    int turn = 0;
    while (winner == ' ' && !check_full_grid(grid)) {
        print_grid(grid);
        move(grid, turn % 2? 'O' : 'X');
        winner = check_winner(grid);
        turn++;
    }

    print_grid(grid);
    if (winner != ' ') printf("%c WINNNNS\n", winner);
    else printf("DRAW!!!\n");

    return 0;
}