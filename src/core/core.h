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
    bool is_mine;
    CellState cell_state;
    short num_surr_mines;
};
typedef struct MineCell MineCell;

/**
 * Struct for the field that contains cells.
 */
struct MineField {
    size_t length;
    size_t height;
    MineCell *cells;
    int num_mines;
    int num_revealed;
};
typedef struct MineField MineField;


/**
 * Create and initialize a mine field
 * @param length Length of the field
 * @param height Height of the field
 * @param num_mines Numbers of mines
 * @return The initialized field
 */
MineField *createField(int length, int height, int num_mines);

/**
 *
 * @param field
 */
void freeField(MineField *field);

/**
 * Get cell struct from the coordinate
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
 * Calculate the surrounding cells surround the certain coordinates.
 * @param field Mine field
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @return Num of the surrounding mines, the maximum is 8
 */
static short calcSurroundMineNum(MineField *field, int x, int y);

#endif //MINESWEEPER_CORE_H
