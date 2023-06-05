
#ifndef MINESWEEPER_CORE_HPP
#define MINESWEEPER_CORE_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>

extern "C" {
#include "core.h"
}

enum GameStatus {
    UNINITIALIZED = -1,
    RUNNING = 0,
    WIN = 1,
    LOSE = 2
};

struct GameState {
    GameStatus status;
    sf::Time time;
    int num_remaining_mines;
};


class GameCore {

private:
    c_MineField *field_;

public:
    /**
     * Store the game status
     */
    GameStatus status;
    sf::Clock timer;

    /**
     * Create a mine field
     * @param length Length of the field
     * @param height Height of the field
     * @param num_mines Numbers of mines
     */
    GameCore(int length, int height, int num_mines) : status(UNINITIALIZED) {
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
        status = RUNNING;
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
        if (status == UNINITIALIZED) {
            scatterMines(x, y);
            initField();
            timer.restart();
        }
        status = c_revealCell(field_, x, y) ? LOSE : RUNNING;
        checkIfWin();
    }

    void revealSurrCells(int x, int y) {
        assert(status == RUNNING || UNINITIALIZED);
        status = c_revealSurrCells(field_, x, y) ? LOSE : RUNNING;
        checkIfWin();
    }

    void markFlagCell(int x, int y) {
        assert(status == RUNNING || UNINITIALIZED);
        c_markFlagCell(field_, x, y);
    }

    void markUnknownCell(int x, int y) {
        assert(status == RUNNING || UNINITIALIZED);
        c_markUnknownCell(field_, x, y);
    }

    void clearMarkCell(int x, int y) {
        assert(status == RUNNING || UNINITIALIZED);
        c_clearMarkCell(field_, x, y);
    }

    void checkIfWin() {
        if (status == RUNNING)
            status = c_checkIfWin(field_) ? WIN : RUNNING;
    }

    GameState getState() {
        return {status, timer.getElapsedTime(), field_->num_mines - field_->num_flagged};
    }
};


#endif //MINESWEEPER_CORE_HPP
