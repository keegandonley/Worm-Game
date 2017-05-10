#include <iostream>
#include <curses.h>

#ifndef __BOARD
#define __BOARD

class Board {
public:
    Board (int row, int col);
    void print();
    struct coord {
        int x;
        int y;
    };
    int getMatrixVal(int x, int y) { return board[x][y]; }
    void removeFromFree(int x, int y);
    void addToFree(int x, int y);
    int  getLastIdx() { return lastIdx; }
    coord getCoords(int idx) { return freepool[idx]; }
    coord& getCurrent() { return currentPos; }
    coord& getPrevious() { return previousPos; }
    coord& getMunchie() { return currentMunchiePos; }
    bool& isLiveMunchie() { return liveMunchie; }
    int& getMunchieValue() { return munchieValue; }
    int& getMunchieCountdown() { return munchieCountdown; }
    int& getScore() { return totalScore; }
    bool& isWin() { return win; }

    void setWorm(int numRows, int numCols);
    void setHeadAndTail(int h, int t) {head = h; tail = t; }
    bool growWorm(char direction);
    bool moveWorm(char direction);
    int getNextIdx() { return tail + 1; }
    int moveTail();
    int moveHead(coord current);


private:

    int     lastIdx;
    int     **board;
    coord   *freepool;
    coord   *worm;
    int     wormLastIdx;

    int     head;
    int     tail;

    bool    activeMunchie;
    bool    liveMunchie;
    int     munchieValue;
    int     munchieCountdown;
    int     totalScore;
    coord   currentPos;
    coord   previousPos;
    coord   currentMunchiePos;

    bool    win;

};

#endif
