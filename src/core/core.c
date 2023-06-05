//
// Created by Catslashbin on 23-4-30.
//

#include "core.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandInt(int m) {
    assert(m > 0);
    static bool initialized = false;
    if (!initialized) {
        srand(time(NULL)); // NOLINT(cert-msc51-cpp)
        initialized = true;
    }
    return rand() % m; // NOLINT(cert-msc50-cpp)
}

#define IS_AVAILABLE_SURR (i >= 0 && i < field->length && j >= 0 && j < field->height && !(i == x && j == y))

c_MineField *c_createField(int length, int height, int num_mines) {

    assert(length > 0 && height > 0 && num_mines <= length * height && num_mines >= 0);

    c_MineField *field = malloc(sizeof(c_MineField));
    field->cells = malloc(sizeof(c_MineCell) * length * height);

    field->length = length;
    field->height = height;
    field->num_revealed = 0;
    field->num_flagged = 0;
    field->num_mines = num_mines;

    for (size_t i = 0; i < length * height; ++i) {
        field->cells[i] = (c_MineCell){false, HIDDEN};
    }

    return field;
}

void c_initField(c_MineField *field) {
    for (size_t x = 0; x < field->length; ++x) {
        for (size_t y = 0; y < field->height; ++y) {
            c_MineCell *cell = c_getCell(field, (int) x, (int) y);
            cell->num_surr_mines = c_calcSurroundMineNum(field, (int) x, (int) y);
        }
    }
}

void c_scatterMines(c_MineField *field, int init_x, int init_y) {
    for (size_t i = 0; i < field->num_mines; ++i) {
        int x = getRandInt((int) field->length), y = getRandInt((int) field->height);
        c_MineCell *cell = c_getCell(field, x, y);

        // Check if a mine is already at that cell, or the cell is the initial cell.
        if (cell->is_mine || (x == init_x && y == init_y)) {
            i--;
        } else {
            cell->is_mine = true;
        }
    }
}

void c_freeField(c_MineField *field) {
    free(field);
}

c_MineCell *c_getCell(c_MineField *field, int x, int y) {
    assert(x >= 0 && x < field->length && y >= 0 && y < field->height);
    return &field->cells[y * field->length + x];
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
bool c_revealCell(c_MineField *field, int x, int y) {

    c_MineCell *cell = c_getCell(field, x, y);

    // Ignore the cell if it has already been revealed or flagged
    if (cell->cell_state == REVEALED || cell->cell_state == FLAGGED) {
        return false;
    }

    // Reveal the cell
    cell->cell_state = REVEALED;
    field->num_revealed++;
    if (cell->is_mine) {
        return true;
    }

    // If the cell is "blank", open the surrounding cells recursively
    if (cell->num_surr_mines == 0) {
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (IS_AVAILABLE_SURR) {
                    // c_clearMarkCell(field, i, j); // Removes flags on cell
                    c_revealCell(field, i, j);
                }
            }
        }
    }

    return false;
}
#pragma clang diagnostic pop

bool c_revealSurrCells(c_MineField *field, int x, int y) {

    // Ignore the cell if it's not revealed
    if (c_getCell(field, x, y)->cell_state != REVEALED)
        return false;

    int num_surr_flagged = 0;
    bool is_incorrectly_flagged = false;

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (IS_AVAILABLE_SURR) {
                c_MineCell *cell = c_getCell(field, i, j);
                num_surr_flagged += cell->cell_state == FLAGGED;
                if ((cell->cell_state == FLAGGED) && !cell->is_mine) {
                    is_incorrectly_flagged = true;
                }
            }
        }
    }

    // If the flagged mines does not equal to the num_surr_mines, ignore the cell.
    if (num_surr_flagged != c_getCell(field, x, y)->num_surr_mines)
        return false;

    // If the mine is incorrectly flagged, stop the game before revealing the cells
    if (is_incorrectly_flagged)
        return true;

    // Open the cells recursively
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (IS_AVAILABLE_SURR) {
                // NOTE: the `revealCell` will handel the cells marked with flag or already revealed.
                c_revealCell(field, i, j);
            }
        }
    }
    return false;
}

void c_markFlagCell(c_MineField *field, int x, int y) {
    c_MineCell *cell = c_getCell(field, x, y);
    if (cell->cell_state == HIDDEN || cell->cell_state == UNKNOWN) {
        cell->cell_state = FLAGGED;
        field->num_flagged++;
    }
}

void c_markUnknownCell(c_MineField *field, int x, int y) {
    c_MineCell *cell = c_getCell(field, x, y);
    switch (cell->cell_state) {
        case FLAGGED:
            field->num_flagged--;
            // NO BREAK HERE!
        case HIDDEN:
            cell->cell_state = UNKNOWN;
            break;
        default:
            break;
    }
}

void c_clearMarkCell(c_MineField *field, int x, int y) {
    c_MineCell *cell = c_getCell(field, x, y);
    switch (cell->cell_state) {
        case FLAGGED:
            field->num_flagged--;
            // NO BREAK HERE!
        case UNKNOWN:
            cell->cell_state = HIDDEN;
            break;
        default:
            break;
    }
}

bool c_checkIfWin(c_MineField *field) {
    return field->num_revealed == field->length * field->height - field->num_mines;
}

static int c_calcSurroundMineNum(c_MineField *field, int x, int y) {
    int n_surr_mines = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (IS_AVAILABLE_SURR)
                n_surr_mines += c_getCell(field, i, j)->is_mine;
        }
    }
    return n_surr_mines;
}

