//
// Created by Catslashbin on 23-4-30.
//

#include "core/core.h"
#include <stdbool.h>
#include <stdio.h>

#define CLI_DISPLAY_UNREVEALED "."
#define CLI_DISPLAY_MINE "*"
#define CLI_DISPLAY_FLAG "!"
#define CLI_DISPLAY_UNKNOWN "?"

void printField(c_MineField *field, bool reveal_all, int num_steps, int num_mines_guess) {
    printf("%d %d\n", num_steps, num_mines_guess);

    // Print vertical grid
    printf("   ");
    for (int x = 0; x < field->length; x++) {
        printf("%d ", x);
    }
    printf("\n");

    printf("  ");
    for (int x = 0; x < field->length; x++) {
        printf("--");
    }
    printf("\n");

    for (int y = 0; y < field->height; ++y) {
        printf("%d| ", y);
        for (int x = 0; x < field->length; ++x) {
            c_MineCell *cell = c_getCell(field, x, y);
            if (reveal_all) {
                if (cell->is_mine) {
                    printf(CLI_DISPLAY_MINE " ");
                } else if (cell->cell_state == HIDDEN) {
                    printf(CLI_DISPLAY_UNREVEALED " ");
                } else if (cell->cell_state == FLAGGED) {
                    printf(CLI_DISPLAY_FLAG " ");
                } else if (cell->cell_state == UNKNOWN) {
                    printf(CLI_DISPLAY_UNKNOWN " ");
                } else {
                    printf("%d ", cell->num_surr_mines);
                }
            } else {
                if (cell->cell_state == HIDDEN) {
                    printf(CLI_DISPLAY_UNREVEALED " ");
                } else if (cell->cell_state == FLAGGED) {
                    printf(CLI_DISPLAY_FLAG " ");
                } else if (cell->cell_state == UNKNOWN) {
                    printf(CLI_DISPLAY_UNKNOWN " ");
                } else if (cell->is_mine) {
                    printf(CLI_DISPLAY_MINE " ");
                } else {
                    printf("%d ", cell->num_surr_mines);
                }
            }
        }
        printf("\n");
    }
}

int main() {

    // Load configs & create field
    int length = 9, height = 9, num_mines = 10;
    c_MineField *field = c_createField(length, height, num_mines);
    c_scatterMines(field, 5, 5);
    c_initField(field);

    printField(field, true, 0, num_mines);
    printf("Start!\n\n");

    bool is_revealed_mine = false;
    int x, y, action, num_steps = 0;

    // Main game loop in CLI
    while (true) {

        // Handle user input
        scanf("%d %d %d", &action, &y, &x);
        switch (action) {
            case 1:
                is_revealed_mine = c_revealCell(field, x, y);
                break;
            case 2:
                c_markFlagCell(field, x, y);
                break;
            case 3:
                c_markUnknownCell(field, x, y);
                break;
            case 4:
                c_clearMarkCell(field, x, y);
                break;
            case 9:
                is_revealed_mine = c_revealSurrCells(field, x, y);
                break;
            default:
                return -1;
        }
        num_steps++;

        if (is_revealed_mine) {
            printf("Hit mine, you lose\n");
            printField(field, true, num_steps, num_mines - field->num_flagged);
            break;
        }

        if (c_checkIfWin(field)) {
            printf("Game over, you win\n");
            printField(field, true, num_steps, num_mines - field->num_flagged);
            break;
        }

        printf("Game in progress\n");
        printField(field, false, num_steps, num_mines - field->num_flagged);
    }

    c_freeField(field);
    return 0;
}
