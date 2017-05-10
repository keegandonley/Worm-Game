// Keegan Donley
// CS 315
// Project 5

// This file contains a function that is used to render the display
// with a given offset (this makes room for the stats at the top
// of the screen)
#include <curses.h>

#ifndef __MOVE
#define __MOVE

const int verticalOffset = 1;

inline void moveChar(int x, int y, char c) {
    mvaddch(x + verticalOffset, y ,c);
}

#endif
