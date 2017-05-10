#include "board.hpp"
#include "directions.hpp"
#include <iostream>
#include <curses.h>
#include "move.hpp"

// Initializes the game board with all of the proper values.
Board::Board(int row, int col) {
    board = new int * [row];
    for (int i = 0; i < row; i++) {
        board[i] = new int[col];
    }

    int fp    = (row - 2) * (col - 2);
    currentPos.x = row/2;
    currentPos.y = col/2 - 4;
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

// Removes a given coordinate from the free pool if it is free
void Board::removeFromFree(int x, int y) {
    if (board[x][y] != -1) {
        int location = board[x][y]; // This is the freepool index to delete
        coord swap = freepool[lastIdx]; // This is the coordinates we must keep!
        coord temp = freepool[location]; // This is the coordinates we are deleting!
        freepool[location] = swap;
        freepool[lastIdx] = temp;
        board[swap.x][swap.y] = location;
        board[x][y] = - 1;
        lastIdx--;
    }
}

// Adds a given coordinate to the free pool if it isn't already free
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

// Grows the worm (doesn't cut off the tail when moving)
bool Board::growWorm(char direction) {
    if (direction == LEFT) {
        (getCurrent().y)--;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    } else if (direction == DOWN) {
        (getCurrent().x)++;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    } else if (direction == RIGHT) {
        (getCurrent().y)++;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    } else if (direction == UP) {
        (getCurrent().x)--;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    }
    if (direction == UP || direction == DOWN || direction == LEFT || direction == RIGHT) {
        moveHead(getCurrent());
        coord previous = getPrevious();
        moveChar(previous.x, previous.y, 'o');
        moveChar(worm[head].x, worm[head].y, '@');
        getPrevious() = getCurrent();
    }
    return true;
}

// Moves the worm - (moves the head and tail together)
bool Board::moveWorm(char direction) {
    if (direction == LEFT) {
        (getCurrent().y)--;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    } else if (direction == DOWN) {
        (getCurrent().x)++;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    } else if (direction == RIGHT) {
        (getCurrent().y)++;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    } else if (direction == UP) {
        (getCurrent().x)--;
        if (board[getCurrent().x][getCurrent().y] == -1) {
            return false;
        }
    }
    if (direction == UP || direction == DOWN || direction == LEFT || direction == RIGHT) {
        moveChar(worm[tail].x, worm[tail].y, ' ');
        moveTail();
        moveHead(getCurrent());
        coord previous = getPrevious();
        moveChar(previous.x, previous.y, 'o');
        moveChar(worm[head].x, worm[head].y, '@');
        getPrevious() = getCurrent();
    }
    return true;
}

// Adjusts the worm head in the circular array
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

// Adjusts the worm tail in the circular array
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

// Initilizes the worm at the center of the screen
void Board::setWorm(int numRows, int numCols) {
    coord temp;
    temp.x = numRows / 2;
    temp.y = numCols / 2 - 5;
    for (int i = 0; i < 8; i++) {
        temp.y++;
        worm[i] = temp;
        if (i == 0) {
            moveChar(temp.x, temp.y, '@');
        } else {
            moveChar(temp.x, temp.y, 'o');
        }
        removeFromFree(temp.x, temp.y);
    }
    head = 0;
    tail = 7;
}
