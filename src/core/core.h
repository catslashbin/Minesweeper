//
// Created by Catslashbin on 23-4-30.
//

#ifndef MINESWEEPER_CORE_H
#define MINESWEEPER_CORE_H

#include <stdbool.h>
#include <stdio.h>

enum CellState { HIDDEN = 0,
                 REVEALED = 1,
                 FLAGGED = 2 };
typedef enum CellState CellState;

/**
 * Struct for cells in the game.
 */
struct MineCell {
    int x, y;
    bool is_mine;
    CellState cell_state;
    short num_surround_mines;
};
typedef struct MineCell MineCell;

/**
 * Struct for the field that contains cells.
 */
struct MineField {
    size_t length;
    size_t height;
    MineCell *cells;
};
typedef struct MineField MineField;


/**
 * Create and initialize a mine field
 * @param length Length of the field
 * @param height Height of the field
 * @param num_mines Numbers of mines
 * @return The initialized field
 */
MineField *createField(size_t length, size_t height, size_t num_mines);

/**
 *
 * @param field
 */
void freeField(MineField *field);

/**
 *
 * @param x
 * @param y
 * @return
 */
MineCell *getCell(MineField *field, int x, int y);

/**
 * Open a cell in the field, and update the field.
 * @param field Mine field
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @return Is the opened cell contains a mine
 */
bool revealCell(MineField *field, int x, int y);

/**
 * Check if the user wins.
 * @param field Mine field
 * @return If the user wins
 */
bool checkIfWin(MineField *field);

/**
 * Get all the available cells surround the certain coordinates,
 * and put pointers that point to the surrounded cells into the buffer.
 * @param field Mine field
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @param surr_cells Buffer which contains pointers to the surrounded cells
 * @return Num of the surrounding cells, the maximum is 8
 */
static size_t getSurroundCells(MineField *field, int x, int y, MineCell **surr_cells_buff);

#endif //MINESWEEPER_CORE_H
