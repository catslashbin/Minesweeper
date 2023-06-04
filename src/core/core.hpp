
#ifndef MINESWEEPER_CORE_HPP
#define MINESWEEPER_CORE_HPP

#include <cassert>
extern "C" {
#include "core.h"
}

enum GameState {
    UNINITIALIZED = -1,
    RUNNING = 0,
    WIN = 1,
    LOSE = 2
};


class GameCore {

private:
    c_MineField *field_;

public:
    /**
     * Store the game state
     */
    GameState state;

    /**
     * Create a mine field
     * @param length Length of the field
     * @param height Height of the field
     * @param num_mines Numbers of mines
     */
    GameCore(int length, int height, int num_mines) : state(UNINITIALIZED) {
        field_ = c_createField(length, height, num_mines);
    }

    /**
     * Scatter mines in the field randomly.
     * @note The function will avoid scatter mine at (init_x, init_y), so the user will not hit a mine at the first click.
     * @param field
     * @param init_x
     * @param init_y
     */
    void scatterMines(int init_x, int init_y) {
        c_scatterMines(field_, init_x, init_y);
    }

    /**
     * Init the mine field, including calculating the surrounding mines num of each cell.
     * @param field
     */
    void initField() {
        c_initField(field_);
        state = RUNNING;
    }

    /**
     * Get cell struct from the coordinate
     * @param x
     * @param y
     * @return
     */
    c_MineCell *getCell(int x, int y) {
        return c_getCell(field_, x, y);
    }

    void revealCell(int x, int y) {
        if (state == UNINITIALIZED) {
            scatterMines(x, y);
            initField();
        }
        state = c_revealCell(field_, x, y) ? LOSE : RUNNING;
        checkIfWin();
    }

    void revealSurrCells(int x, int y) {
        assert(state == RUNNING || UNINITIALIZED);
        state = c_revealSurrCells(field_, x, y) ? LOSE : RUNNING;
        checkIfWin();
    }

    void markFlagCell(int x, int y) {
        assert(state == RUNNING || UNINITIALIZED);
        c_markFlagCell(field_, x, y);
    }

    void markUnknownCell(int x, int y) {
        assert(state == RUNNING || UNINITIALIZED);
        c_markUnknownCell(field_, x, y);
    }

    void clearMarkCell(int x, int y) {
        assert(state == RUNNING || UNINITIALIZED);
        c_clearMarkCell(field_, x, y);
    }

    void checkIfWin() {
        if (state == RUNNING)
            state = c_checkIfWin(field_) ? WIN : RUNNING;
    }
};


#endif //MINESWEEPER_CORE_HPP
