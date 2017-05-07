#include "board.hpp"
#include <iostream>
Board::Board(int row, int col) {
    board = new int * [row];
    for (int i = 0; i < row; i++) {
        board[i] = new int[col];
    }

    int fp    = (row - 2) * (col - 2);
    lastIdx   = fp - 1;
    freepool  = new coord [fp];
    worm      = new coord [fp]; 
    int count = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // KEEGAN READ THIS: NEVER CHANGE THE FUCKING POOL WITHOUT CHANGING THE BOARD
            if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                board[i][j]     = -1;
            } else {
                coord current;
                current.x       = i;
                current.y       = j;
                board[i][j]     = count;
                freepool[count] = current;
                count++;
            }
        }
    }
}
