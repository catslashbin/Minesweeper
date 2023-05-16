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

void printField(MineField *field, bool reveal_all, int num_steps, int num_mines) {
    printf("%d %d\n", num_steps, num_mines);
    for (int y = 0; y < field->height; ++y) {
        for (int x = 0; x < field->length; ++x) {
            MineCell *cell = getCell(field, x, y);
            if (reveal_all) {
                if (cell->is_mine) {
                    printf(CLI_DISPLAY_MINE);
                } else if (cell->cell_state == HIDDEN) {
                    printf(CLI_DISPLAY_UNREVEALED);
                } else if (cell->cell_state == FLAGGED) {
                    printf(CLI_DISPLAY_FLAG);
                } else if (cell->cell_state == UNKNOWN) {
                    printf(CLI_DISPLAY_UNKNOWN);
                } else {
                    printf("%d", cell->num_surr_mines);
                }
            } else {
                if (cell->cell_state == HIDDEN) {
                    printf(CLI_DISPLAY_UNREVEALED);
                } else if (cell->cell_state == FLAGGED) {
                    printf(CLI_DISPLAY_FLAG);
                } else if (cell->cell_state == UNKNOWN) {
                    printf(CLI_DISPLAY_UNKNOWN);
                } else if (cell->is_mine) {
                    printf(CLI_DISPLAY_MINE);
                } else {
                    printf("%d", cell->num_surr_mines);
                }
            }
        }
        printf("\n");
    }
}

int main() {

    // Load configs & create field
    int level, length, height, num_mines;
    scanf("%d", &level);
    switch (level) {
        case 1:
            length = height = 9;
            num_mines = 10;
            break;
        case 2:
            length = height = 16;
            num_mines = 40;
            break;
        case 3:
            length = 16;
            height = 30;
            num_mines = 99;
            break;
        case 4: // Customize
            scanf("%d %d %d", &height, &length, &num_mines);
            break;
        default:
            return -1;
    }
    MineField *field = createField(length, height, num_mines);

    // Load & init field
    char inp;
    for (size_t i = 0; i < length * height; ++i) {
        scanf("%c", &inp);
        if (inp == '.') {
            field->cells[i].is_mine = false;
        } else if (inp == '*') {
            field->cells[i].is_mine = true;
        } else {
            --i;
            continue;
        }
    }
    initField(field);

    bool is_revealed_mine = false;
    int x, y, action, num_steps = 0;

    // Main game loop in CLI
    while (true) {

        // Handle user input
        scanf("%d %d %d", &action, &y, &x);
        x--;
        y--;
        switch (action) {
            case 1:
                is_revealed_mine = revealCell(field, x, y);
                break;
            case 2:
                markFlagCell(field, x, y);
                break;
            case 3:
                markUnknownCell(field, x, y);
                break;
            case 4:
                clearMarkCell(field, x, y);
                break;
            case 9:
                is_revealed_mine = revealSurrCells(field, x, y);
                break;
            default:
                return -1;
        }
        num_steps++;

        if (is_revealed_mine) {
            printf("Hit mine, you lose\n");
            printField(field, true, num_steps, num_mines);
            break;
        }

        if (checkIfWin(field)) {
            printf("Game over, you win\n");
            printField(field, true, num_steps, num_mines);
            break;
        }

        printf("Game in progress\n");
        printField(field, false, num_steps, num_mines);
    }

    freeField(field);
    return 0;
}
