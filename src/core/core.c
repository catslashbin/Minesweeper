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


MineField *createField(size_t length, size_t height, size_t num_mines) {

    assert(length > 0 && height > 0 && num_mines <= length * height);

    MineField *field = malloc(sizeof(MineField));
    field->cells = malloc(sizeof(MineCell) * length * height);

    // Init field
    for (size_t i = 0; i < length * height; ++i) {
        field->cells[i] = (MineCell){(int) (i % length), (int) (i / length), false, HIDDEN, 0};
    }

    // Scatter mines
    for (size_t i = 0; i < num_mines; ++i) {

        int x = getRandInt((int) length), y = getRandInt((int) height);
        MineCell *cell = getCell(field, x, y);

        // A mine is already at that cell. Ignore
        if (cell->is_mine) {
            i--;
            continue;
        }

        // Update cell
        cell->is_mine = true;

        // Update surr cells
        MineCell *surr_mines_buff[9];
        size_t n = getSurroundCells(field, x, y, surr_mines_buff);
        for (size_t j = 0; j < n; ++j) {
            surr_mines_buff[j]->num_surround_mines++;
        }
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

    cell->cell_state = REVEALED;

    // If the cell contains a mine, the game is over
    if (cell->is_mine) {
        return true;
    }

    // If the cell is "blank", recursively open the surrounding cells
    if (cell->num_surround_mines == 0) {
        MineCell *surr_cells_buff[8];
        size_t num_surr_cells = getSurroundCells(field, x, y, surr_cells_buff);
        for (size_t i = 0; i < num_surr_cells; i++) {
            revealCell(field, surr_cells_buff[i]->x, surr_cells_buff[i]->y);
        }
    }

    return false;
}
#pragma clang diagnostic pop

static size_t getSurroundCells(MineField *field, int x, int y, MineCell **surr_cells_buff) {
    size_t num_surr_cells = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < field->length && j >= 0 && j < field->height && !(i == x && j == y)) {
                surr_cells_buff[num_surr_cells] = getCell(field, x, y);
                num_surr_cells++;
                if (num_surr_cells == 8) {
                    return num_surr_cells;
                }
            }
        }
    }
    return num_surr_cells;
}
