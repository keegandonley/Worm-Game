#include <curses.h>
#include <cstdlib>
#include <iostream>
#include "getChar.hpp"
#include "board.hpp"
#include <string>
#include <iomanip>
void startup( void );
void terminate( void );

int main(int argc, const char * argv[])
{
    if (argc < 3) {
        std::cout << "Please enter the screen size\n";
        exit (1);
    }

    int numRows = atoi(argv[1]);
    int numCols = atoi(argv[2]);

    if (numRows < 10 || numRows > 25 || numCols < 10 || numCols > 80) {
        std::cout << "Please enter a screen size between 10x10 and 25x80\n";
        exit (2);
    }
    startup();
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (i == 0 || i == numRows - 1 || j == 0 || j == numCols - 1)
                mvaddch(i,j,'*');
        }
    }
    refresh();
    /*Board * game = new Board(numRows, numCols);
    for (int i = 0; i < numRows; i++) {
	for (int j = 0; j < numCols; j++) {
		std::cout << std::setw(3) << game->getMatrixVal(i,j) << " "; 
	}
	std::cout << std::endl;
    }*/
    char c;
    int x = numRows/2;
    int y = numCols/2;
    int oldx = x;
    int oldy = y;
    mvaddch(x,y,'X');
    refresh(); 
    while (c = get_char()) {
	oldx = x;
	oldy = y;
	if (c == 'q') {
	    break;
	} else if (c == 'a') {
		y--;
	} else if (c == 's') {
		x++;
	} else if (c == 'd') {
		y++;
	} else if (c == 'w') {
		x--;
	}

	if (x == 0 || x == numRows - 1 || y == 0 || y == numCols - 1)
		break;
	mvaddch(oldx,oldy,' ');
	mvaddch(x,y,'X');
	refresh();
    } 
    terminate();
    return 0;
}

void startup( void )
{
    initscr();	 /* activate the curses */
    curs_set(0);/* do not display the cursor */
    clear();	 /* clear the screen that curses provides */
    noecho();	 /* prevent the input chars to be echoed to the screen */
    cbreak();	 /* change the stty so that characters are delivered to the
    program as they are typed--no need to hit the return key!*/
}

void terminate( void )
{
    mvcur( 0, COLS - 1, LINES - 1, 0 );
    clear();
    refresh();
    endwin();
}
