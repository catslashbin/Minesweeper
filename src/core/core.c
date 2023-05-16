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

    assert(length > 0 && height > 0 && num_mines <= length * height && num_mines >= 0);

    MineField *field = malloc(sizeof(MineField));
    field->cells = malloc(sizeof(MineCell) * length * height);

    field->length = length;
    field->height = height;
    field->num_revealed = 0;
    field->num_mines = num_mines;

    for (size_t i = 0; i < length * height; ++i) {
        field->cells[i] = (MineCell){false, HIDDEN};
    }

    return field;
}

void initField(MineField *field) {
    for (size_t x = 0; x < field->length; ++x) {
        for (size_t y = 0; y < field->height; ++y) {
            MineCell *cell = getCell(field, (int) x, (int) y);
            cell->num_surr_mines = calcSurroundMineNum(field, (int) x, (int) y);
        }
    }
}

void scatterMines(MineField *field, int init_x, int init_y) {
    for (size_t i = 0; i < field->num_mines; ++i) {
        int x = getRandInt((int) field->length), y = getRandInt((int) field->height);
        MineCell *cell = getCell(field, x, y);

        // Check if a mine is already at that cell, or the cell is the initial cell.
        if (cell->is_mine || (x == init_x && y == init_y)) {
            i--;
        } else {
            cell->is_mine = true;
        }
    }
}

void freeField(MineField *field) {
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
                if (i >= 0 && i < field->length && j >= 0 && j < field->height && !(i == x && j == y))
                    revealCell(field, i, j);
            }
        }
    }

    return false;
}
#pragma clang diagnostic pop

bool revealSurrCells(MineField *field, int x, int y) {
    bool is_hit_mine = false;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < field->length && j >= 0 && j < field->height) {
                // NOTE: the `revealCell` will handel the cells marked with flag.
                is_hit_mine = revealCell(field, i, j) || is_hit_mine;
            }
        }
    }
    return is_hit_mine;
}

void markFlagCell(MineField *field, int x, int y) {
    MineCell *cell = getCell(field, x, y);
    if (cell->cell_state == HIDDEN || cell->cell_state == UNKNOWN)
        cell->cell_state = FLAGGED;
}

void markUnknownCell(MineField *field, int x, int y) {
    MineCell *cell = getCell(field, x, y);
    if (cell->cell_state == HIDDEN || cell->cell_state == FLAGGED)
        cell->cell_state = UNKNOWN;
}

void clearMarkCell(MineField *field, int x, int y) {
    MineCell *cell = getCell(field, x, y);
    if (cell->cell_state == FLAGGED || cell->cell_state == UNKNOWN)
        cell->cell_state = HIDDEN;
}

bool checkIfWin(MineField *field) {
    return field->num_revealed == field->length * field->height - field->num_mines;
}

static int calcSurroundMineNum(MineField *field, int x, int y) {
    int n_surr_mines = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < field->length && j >= 0 && j < field->height && !(i == x && j == y))
                n_surr_mines += getCell(field, i, j)->is_mine;
        }
    }
    return n_surr_mines;
}
