#include "board.hpp"
#include <iostream>
Board::Board(int row, int col) {
    board = new int * [row];
    for (int i = 0; i < row; i++) {
        board[i] = new int[col];
    }

    int fp    = (row - 2) * (col - 2);
    currentPos.x = row/2;
    currentPos.y = col/2;
    activeMunchie = false;
    munchieValue = 0;
    munchieCountdown = 0;
    liveMunchie = false;
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

void Board::removeFromFree(int x, int y) {
    int location = board[x][y]; // This is the freepool index to delete
    coord swap = freepool[lastIdx]; // This is the coordinates we must keep!
    coord temp = freepool[location]; // This is the coordinates we are deleting!
    freepool[location] = swap;
    freepool[lastIdx] = temp;
    board[swap.x][swap.y] = location;
    board[x][y] = - 1;
}
