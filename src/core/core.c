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
        field->cells[i] = (MineCell){false, false, false, 0};
    }

    // Scatter mines
    for (size_t i = 0; i < num_mines; ++i) {

        int x = getRandInt((int) length), y = getRandInt((int) height);
        MineCell *cell = getCell(field, x, y);

        if (cell->is_mine) {
            i--;
            continue;
        }

        // Update cell
        cell->is_mine = true;

        // Update surr cells
        MineCell *surr_mines_buff[9];
        size_t n = getSurroundCells(x, y, surr_mines_buff);
        for (size_t j = 0; j < n; ++j) {
            surr_mines_buff[j]->num_surround_mines++;
        }
    }

    return field;
}

MineCell *getCell(MineField *field, int x, int y) {
    assert(x >= 0 && x < field->length && y >= 0 && y < field->height);
    return &field->cells[y * field->length + x];
}

static size_t getSurroundCells(int x, int y, MineCell **surr_cells_buff) {
}
