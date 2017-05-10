#include <curses.h>

#ifndef __MOVE
#define __MOVE

const int verticalOffset = 1;

inline void moveChar(int x, int y, char c) {
    mvaddch(x + verticalOffset, y ,c);
}

#endif
