#include "board.hpp"
#include "directions.hpp"
#include <iostream>
#include <curses.h>

Board::Board(int row, int col) {
    board = new int * [row];
    for (int i = 0; i < row; i++) {
        board[i] = new int[col];
    }

    int fp    = (row - 2) * (col - 2);
    currentPos.x = row/2;
    currentPos.y = col/2;
    previousPos.x = currentPos.x;
    previousPos.y = currentPos.y;
    activeMunchie = false;
    munchieValue = 0;
    munchieCountdown = 0;
    liveMunchie = false;
    lastIdx   = fp - 1;
    freepool  = new coord [fp];
    worm      = new coord [fp];
    wormLastIdx = fp - 1;
    head = tail = 0;
    totalScore = 0;
    int count = 0;
    win = false;

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
    lastIdx--;
}

void Board::addToFree(int x, int y) {
    if (board[x][y] == -1) {
        Board::coord temp;
        temp.x = x;
        temp.y = y;
        lastIdx++;
        freepool[lastIdx] = temp;
        board[x][y] = lastIdx;
    }
}

void Board::growWorm(char direction) {
    if (direction == LEFT) {
        (getCurrent().y)--;
    } else if (direction == DOWN) {
        (getCurrent().x)++;
    } else if (direction == RIGHT) {
        (getCurrent().y)++;
    } else if (direction == UP) {
        (getCurrent().x)--;
    }
    if (direction == UP || direction == DOWN || direction == LEFT || direction == RIGHT) {
        moveHead(getCurrent());
        coord previous = getPrevious();
        mvaddch(previous.x, previous.y, 'o');
        mvaddch(worm[head].x, worm[head].y, '@');
        getPrevious() = getCurrent();
    }
}

void Board::moveWorm(char direction) {
    if (direction == LEFT) {
        (getCurrent().y)--;
    } else if (direction == DOWN) {
        (getCurrent().x)++;
    } else if (direction == RIGHT) {
        (getCurrent().y)++;
    } else if (direction == UP) {
        (getCurrent().x)--;
    }
    if (direction == UP || direction == DOWN || direction == LEFT || direction == RIGHT) {
        mvaddch(worm[tail].x, worm[tail].y, ' ');
        moveTail();
        moveHead(getCurrent());
        coord previous = getPrevious();
        mvaddch(previous.x, previous.y, 'o');
        mvaddch(worm[head].x, worm[head].y, '@');
        getPrevious() = getCurrent();
    }
}

int Board::moveHead(coord current) {
    int temp = head;
    removeFromFree(worm[temp].x, worm[temp].y);
    temp = temp - 1;
    if (temp < 0) {
        temp = wormLastIdx;
    }
    head = temp;
    worm[head] = current;
    return head;
}

int Board::moveTail() {
    int temp = tail;
    addToFree(worm[temp].x, worm[temp].y);
    temp = temp - 1;
    if (temp < 0) {
        temp = wormLastIdx;
    }
    tail = temp;
    return tail;
}

void Board::setWorm(int numRows, int numCols) {
    coord temp;
    temp.x = numRows / 2;
    temp.y = numCols / 2;
    for (int i = 0; i < 8; i++) {
        worm[i] = temp;
        temp.y++;
        mvaddch(temp.x, temp.y, 'o');
        removeFromFree(temp.x, temp.y);
    }
    head = 0;
    tail = 7;
}
