#include <iostream>
#include <curses.h>

#ifndef __BOARD
#define __BOARD

class Board {
public:
    // Initilizes the board
    Board (int row, int col);

    // Struct used to keep track of all points
    struct coord {
        int x;
        int y;
    };

    // Get information about the gurrent game
    int getMatrixVal(int x, int y) { return board[x][y]; }
    void removeFromFree(int x, int y);
    void addToFree(int x, int y);
    int  getLastIdx() { return lastIdx; }

    // Maintain the corrdinates of the current positions
    coord getCoords(int idx) { return freepool[idx]; }
    coord& getCurrent() { return currentPos; }
    coord& getPrevious() { return previousPos; }

    // Retrieve and set munchie and score data
    coord& getMunchie() { return currentMunchiePos; }
    bool& isLiveMunchie() { return liveMunchie; }
    int& getMunchieValue() { return munchieValue; }
    int& getMunchieCountdown() { return munchieCountdown; }
    int& getScore() { return totalScore; }

    // Retrieves and sets the win condition
    bool& isWin() { return win; }

    // Manipulates the worm data
    void setWorm(int numRows, int numCols);
    bool growWorm(char direction);
    bool moveWorm(char direction);
    int moveTail();
    int moveHead(coord current);


private:

    // General game structure
    int     lastIdx;
    int     **board;
    coord   *freepool;

    // Data for the worm
    coord   *worm;
    int     wormLastIdx;
    int     head;
    int     tail;

    // Data for the munchie
    bool    activeMunchie;
    bool    liveMunchie;
    int     munchieValue;
    int     munchieCountdown;

    // Data for the current state
    int     totalScore;
    coord   currentPos;
    coord   previousPos;
    coord   currentMunchiePos;

    // Tracks if the program terminated due to a win or loss
    bool    win;

};

#endif
