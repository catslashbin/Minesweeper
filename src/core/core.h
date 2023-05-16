//
// Created by Catslashbin on 23-4-30.
//

#ifndef MINESWEEPER_CORE_H
#define MINESWEEPER_CORE_H

#include <stdbool.h>
#include <stdio.h>

enum CellState { HIDDEN = 0,
                 REVEALED = 1,
                 FLAGGED = 2,
                 UNKNOWN = 3 };
typedef enum CellState CellState;

/**
 * Struct for cells in the game.
 */
struct MineCell {
    bool is_mine;
    CellState cell_state;
    int num_surr_mines;
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
 * Create a mine field
 * @param length Length of the field
 * @param height Height of the field
 * @param num_mines Numbers of mines
 * @return The field
 */
MineField *createField(int length, int height, int num_mines);

/**
 * Init the mine field, including calculating the surrounding mines num of each cell.
 * @param field
 */
void initField(MineField *field);

/**
 * Scatter mines in the field randomly.
 * @note The function will avoid scatter mine at (init_x, init_y), so the user will not hit a mine at the first click.
 * @param field
 * @param init_x
 * @param init_y
 */
void scatterMines(MineField *field, int init_x, int init_y);

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

bool revealSurrCells(MineField *field, int x, int y);

void markFlagCell(MineField *field, int x, int y);

void markUnknownCell(MineField *field, int x, int y);

void clearMarkCell(MineField *field, int x, int y);

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
static int calcSurroundMineNum(MineField *field, int x, int y);

#endif //MINESWEEPER_CORE_H
