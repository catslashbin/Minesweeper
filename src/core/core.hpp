
#ifndef MINESWEEPER_CORE_HPP
#define MINESWEEPER_CORE_HPP

extern "C" {
#include "core.h"
}

namespace CORE {

    class MineField {

    private:
        ::MineField *field_;

    public:
        /**
         * Create a mine field
         * @param length Length of the field
         * @param height Height of the field
         * @param num_mines Numbers of mines
         */
        MineField(int length, int height, int num_mines) {
            field_ = ::createField(length, height, num_mines);
        }

        /**
         * Scatter mines in the field randomly.
         * @note The function will avoid scatter mine at (init_x, init_y), so the user will not hit a mine at the first click.
         * @param field
         * @param init_x
         * @param init_y
         */
        void scatterMines(MineField *field, int init_x, int init_y) {
            ::scatterMines(field_, init_x, init_y);
        }

        /**
         * Init the mine field, including calculating the surrounding mines num of each cell.
         * @param field
         */
        void initField() {
            ::initField(field_);
        }

        /**
         * Get cell struct from the coordinate
         * @param x
         * @param y
         * @return
         */
        MineCell *getCell(int x, int y) {
            return ::getCell(field_, x, y);
        }

        /**
         * Open a cell in the field, and update the field.
         * @param field Mine field
         * @param x Coordinate x, should be an integer between 0 and length
         * @param y Coordinate y, should be an integer between 0 and height
         * @return Is the opened cell contains a mine
         */
        bool revealCell(int x, int y) {
            return ::revealCell(field_, x, y);
        }

        bool revealSurrCells(int x, int y) {
            return ::revealSurrCells(field_, x, y);
        }

        void markFlagCell(int x, int y) {
            return ::markFlagCell(field_, x, y);
        }

        void markUnknownCell(int x, int y) {
            return ::markUnknownCell(field_, x, y);
        }

        void clearMarkCell(int x, int y) {
            return ::clearMarkCell(field_, x, y);
        }

        /**
         * Check if the user wins.
         * @param field Mine field
         * @return If the user wins
         */
        bool checkIfWin() {
            return ::checkIfWin(field_);
        }
    };

} // namespace CORE

#endif //MINESWEEPER_CORE_HPP
