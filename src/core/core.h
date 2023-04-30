//
// Created by Catslashbin on 23-4-30.
//

#ifndef MINESWEEPER_CORE_H
#define MINESWEEPER_CORE_H

#include <stdbool.h>
#include <stdio.h>

/**
 * Struct for cells in the game.
 */
struct MineCell {
    bool is_mine;
    bool is_revealed;
    bool is_flagged;
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
 * Open a cell in the field, and update the field.
 * @param field Mine field
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @return Is the opened cell a mine
 */
bool openCell(MineField *field, int x, int y);

/**
 * Check if the user wins.
 * @param field Mine field
 * @return If the user wins
 */
bool checkIfWin(MineField *field);

/**
 * Get all the available cells surround the certain coordinates,
 * and put pointers that point to the surrounded cells into the buffer.
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @param surr_cells Buffer which contains pointers to the surrounded cells
 * @return Num of the surrounding cells
 */
static size_t getSurroundCells(int x, int y, MineCell **surr_cells_buff);

/**
 *
 * @param x
 * @param y
 * @return
 */
MineCell *getCell(MineField* field, int x, int y);

#endif //MINESWEEPER_CORE_H
