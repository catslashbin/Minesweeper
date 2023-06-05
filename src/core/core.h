//
// Created by Catslashbin on 23-4-30.
//

#ifndef MINESWEEPER_CORE_H
#define MINESWEEPER_CORE_H

#include <stdbool.h>
#include <stdio.h>

enum c_CellState { HIDDEN = 0,
                 REVEALED = 1,
                 FLAGGED = 2,
                 UNKNOWN = 3 };
typedef enum c_CellState c_CellState;

/**
 * Struct for cells in the game.
 */
struct c_MineCell {
    bool is_mine;
    c_CellState cell_state;
    int num_surr_mines;
};
typedef struct c_MineCell c_MineCell;

/**
 * Struct for the field that contains cells.
 */
struct c_MineField {
    size_t length;
    size_t height;
    c_MineCell *cells;
    int num_mines;
    int num_revealed;
    int num_flagged;
    int num_operations;
};
typedef struct c_MineField c_MineField;


/**
 * Create a mine field
 * @param length Length of the field
 * @param height Height of the field
 * @param num_mines Numbers of mines
 * @return The field
 */
c_MineField *c_createField(int length, int height, int num_mines);

/**
 * Init the mine field, including calculating the surrounding mines num of each cell.
 * @param field
 */
void c_initField(c_MineField *field);

/**
 * Scatter mines in the field randomly.
 * @note The function will avoid scatter mine at (init_x, init_y), so the user will not hit a mine at the first click.
 * @param field
 * @param init_x
 * @param init_y
 */
void c_scatterMines(c_MineField *field, int init_x, int init_y);

/**
 *
 * @param field
 */
void c_freeField(c_MineField *field);

/**
 * Get cell struct from the coordinate
 * @param x
 * @param y
 * @return
 */
c_MineCell *c_getCell(c_MineField *field, int x, int y);

/**
 * Open a cell in the field, and update the field.
 * @param field Mine field
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @return Is the opened cell contains a mine
 */
bool c_revealCell(c_MineField *field, int x, int y);

bool c_revealSurrCells(c_MineField *field, int x, int y);

void c_markFlagCell(c_MineField *field, int x, int y);

void c_markUnknownCell(c_MineField *field, int x, int y);

void c_clearMarkCell(c_MineField *field, int x, int y);

/**
 * Check if the user wins.
 * @param field Mine field
 * @return If the user wins
 */
bool c_checkIfWin(c_MineField *field);

/**
 * Calculate the surrounding cells surround the certain coordinates.
 * @param field Mine field
 * @param x Coordinate x, should be an integer between 0 and length
 * @param y Coordinate y, should be an integer between 0 and height
 * @return Num of the surrounding mines, the maximum is 8
 */
static int c_calcSurroundMineNum(c_MineField *field, int x, int y);

#endif //MINESWEEPER_CORE_H
