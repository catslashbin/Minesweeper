//
// Created by Catslashbin on 23-4-30.
//

#include "core/core.h"
#include <stdbool.h>
#include <stdio.h>

#define INFO /* INFO ENABLED */

#define LENGTH 10
#define HEIGHT 10
#define NUM_MINES 10

#define CLI_DISPLAY_UNREVEALED "."
#define CLI_DISPLAY_MINE "*"
#define CLI_DISPLAY_FLAG "F"

void printField(MineField *field, bool reveal_all) {

    // Print vertical grid
    printf("   ");
    for (int x = 0; x < LENGTH; x++) {
        printf("%d ", x);
    }
    printf("\n");

    printf("  ");
    for (int x = 0; x < LENGTH; x++) {
        printf("--");
    }
    printf("\n");

    for (int y = 0; y < LENGTH; y++) {

        // Print horizontal grid
        printf("%d| ", y);

        for (int x = 0; x < LENGTH; x++) {
            MineCell *cell = getCell(field, x, y);
            if (cell->cell_state == HIDDEN && !reveal_all) {
                printf(CLI_DISPLAY_UNREVEALED" ");
            } else if (cell->cell_state == FLAGGED && !reveal_all) {
                printf(CLI_DISPLAY_FLAG" ");
            } else if (cell->is_mine) {
                printf(CLI_DISPLAY_MINE" ");
            } else {
                printf("%d ", cell->num_surr_mines);
            }
        }
        printf("\n");
    }
}

int main() {

    MineField *field = createField(LENGTH, HEIGHT, NUM_MINES);
    bool is_game_over = false;

    // Main game loop in CLI
    while (!is_game_over) {

        printField(field, false);

        // Handle user input
        int x, y;
        char action;
        printf("Enter coordinate (x,y) and action (r for reveal, f for flag/unflag): ");
        scanf("%d %d %c", &x, &y, &action);

        while (x < 0 || x >= LENGTH || y < 0 || y >= HEIGHT) {
            printf("Invalid coordinate, please enter again: ");
            scanf("%d %d %c", &x, &y, &action);
        }

        if (action == 'r') {

            bool contains_mine = revealCell(field, x, y);
            if (contains_mine) {
                printf("Game over! You revealed a mine.\n");
                is_game_over = true;
            } else if (checkIfWin(field)) {
                printf("Congratulations! You win!\n");
                is_game_over = true;
            }

        } else if (action == 'f') {

            MineCell *cell = getCell(field, x, y);
            if (cell->cell_state == HIDDEN) {
                cell->cell_state = FLAGGED;
            } else if (cell->cell_state == FLAGGED) {
                cell->cell_state = HIDDEN;
            }
        }
    }

    printField(field, true);
    freeField(field);

    return 0;
}
