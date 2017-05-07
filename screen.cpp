#include <curses.h>
#include <cstdlib>
#include <iostream>
#include "getChar.hpp"
#include "board.hpp"
#include <string>
#include <iomanip>
void startup( void );
void terminate( void );
int genMunchies(Board * game);

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
    Board * game = new Board(numRows, numCols);

    bool seenMunchie = false;
    int munchieCount = 0;
    char c;
    mvaddch(game -> getCurrent().x, game -> getCurrent().y, '@');
    genMunchies(game);
    refresh();
    while (c = get_char()) {
        // Generates a munchy whenever needed, and handles checking if we have seen it or not.
        genMunchies(game);

    	if (c == 'q') {
    	    break;
    	} else if (c == 'a') {
    		(game -> getCurrent().y)--;
    	} else if (c == 's') {
    		(game -> getCurrent().x)++;
    	} else if (c == 'd') {
    		(game -> getCurrent().y)++;
    	} else if (c == 'w') {
    		(game -> getCurrent().x)--;
    	}

    	if (game -> getCurrent().x == 0 ||
        game -> getCurrent().x == numRows - 1 ||
        game -> getCurrent().y == 0 ||
        game -> getCurrent().y == numCols - 1)
    		break;
    	if (game -> getMatrixVal(game -> getCurrent().x, game -> getCurrent().y) == -1)
    		break;

        // Remove the previous head location
    	mvaddch(game -> getPrevious().x, game -> getPrevious().y, ' ');
        // Add the head in the new spot
    	mvaddch(game -> getCurrent().x, game -> getCurrent().y, '@');
        game -> getPrevious().x = game -> getCurrent().x;
        game -> getPrevious().y = game -> getCurrent().y;
    	refresh();
    }
    terminate();
    delete game;
    return 0;
}

int genMunchies(Board * game) {
    if (!game -> isLiveMunchie()) {
        int lastIdx = game -> getLastIdx();
        int munchieLocation = rand() % lastIdx;
        Board::coord location = game -> getCoords(munchieLocation);
        game -> getMunchie().x = location.x;
        game -> getMunchie().y = location.y;

        game -> getMunchieValue() = rand() % 8 + 1;
        char val = game -> getMunchieValue() + '0';
        mvaddch(game -> getMunchie().x, game -> getMunchie().y, val);
        game -> isLiveMunchie() = true;

    }

    if (game -> getCurrent().x == game -> getMunchie().x && game -> getCurrent().y == game -> getMunchie().y) {
        game -> getMunchieCountdown() += game -> getMunchieValue();
        game -> getMunchieValue() = 0;
        game -> isLiveMunchie() = false;
    }

    if (game -> getMunchieCountdown() > 0) {
        mvaddch(0,0,'!');
        game -> getMunchieCountdown()--;
    } else {
        mvaddch(0,0,'?');
    }
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
