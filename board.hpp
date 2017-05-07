#include <iostream>
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
    int getMatrixVal(int x, int y) { 
	return board[x][y]; 
    }
private:
    int     lastIdx;
    int   **board;
    coord * freepool;
    coord * worm;

};

#endif
