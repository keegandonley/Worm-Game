#include <curses.h>

#ifndef __MOVE
#define __MOVE

inline void moveChar(int x, int y, char c) {
    mvaddch(x, y ,c);
}

#endif
