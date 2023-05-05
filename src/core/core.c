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

MineField *createField(int length, int height, int num_mines) {

    assert(length > 0 && height > 0 && num_mines <= length * height);

    MineField *field = malloc(sizeof(MineField));
    field->cells = malloc(sizeof(MineCell) * length * height);

    // Init field
    field->length = length;
    field->height = height;
    field->num_revealed = 0;
    field->num_mines = num_mines;
    for (size_t i = 0; i < length * height; ++i) {
        field->cells[i] = (MineCell){false, HIDDEN};
    }

    // Scatter mines
    for (size_t i = 0; i < num_mines; ++i) {
        int x = getRandInt((int) length), y = getRandInt((int) height);
        MineCell *cell = getCell(field, x, y);

        // Check if a mine is already at that cell.
        if (cell->is_mine) {
            i--;
        } else {
            cell->is_mine = true;
        }
    }

    // Calculate surrounding mine nums
    for (int i = 0; i < length * height; ++i) {
        getCell(field, i % length, i / length)->num_surr_mines = calcSurroundMineNum(field, i % length, i / length);
    }

    return field;
}

void freeField(MineField *field) {
    for (size_t i = 0; i < field->length * field->height; ++i) {
        free(&field->cells[i]);
    }
    free(field);
}

MineCell *getCell(MineField *field, int x, int y) {
    assert(x >= 0 && x < field->length && y >= 0 && y < field->height);
    return &field->cells[y * field->length + x];
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
bool revealCell(MineField *field, int x, int y) {

    MineCell *cell = getCell(field, x, y);

    // Ignore the cell if it has already been revealed or flagged
    if (cell->cell_state != HIDDEN) {
        return false;
    }

    // Reveal the cell
    cell->cell_state = REVEALED;
    field->num_revealed++;

    // If the cell contains a mine, the game is over
    if (cell->is_mine) {
        return true;
    }

    // If the cell is "blank", recursively open the surrounding cells
    if (cell->num_surr_mines == 0) {
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i >= 0 && i < field->length && j >= 0 && j < field->height && !(i == x && j == y))
                    revealCell(field, i, j);
            }
        }
    }

    return false;
}
#pragma clang diagnostic pop

bool checkIfWin(MineField *field) {
    return field->num_revealed == field->num_mines;
}

static short calcSurroundMineNum(MineField *field, int x, int y) {
    int num_surr_cells = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < field->length && j >= 0 && j < field->height && !(i == x && j == y))
                num_surr_cells += getCell(field, x, y)->is_mine;
        }
    }
    return num_surr_cells;
}
