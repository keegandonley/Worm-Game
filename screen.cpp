#include <curses.h>
#include <cstdlib>
#include <iostream>
#include "getChar.hpp"
#include "board.hpp"
#include "directions.hpp"
#include <string>
#include <iomanip>

const int verticalOffset = 0;

void startup( void );
void terminate( void );
void genMunchies(Board * game);
bool moveWorm(Board * game, char c, int numRows, int numCols);
void displayChar(int x, int y, char c);
void updateScore(Board * game, int numRows, int numCols);

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
                displayChar(i,j,'*');
        }
    }
    mvaddstr(0,0,"Worm Game");
    mvaddstr(0, numCols-12, "Score: ");
    refresh();
    Board * game = new Board(numRows, numCols);
    game -> setWorm(numRows, numCols);

    bool seenMunchie = false;
    int munchieCount = 0;
    char c;
    genMunchies(game);
    updateScore(game, numRows, numCols);
    refresh();
    while ((c = get_char())) {
        // Generates a munchy whenever needed
        genMunchies(game);
        // Makes the move
        if (!moveWorm(game, c, numRows, numCols)) { break; }
        // Update display
    	updateScore(game, numRows, numCols);
        refresh();
    }
    terminate();
    if (!game -> isWin()) {
        std::cout << "You hit an obstacle!" << std::endl;
        std::cout << "Total points: " << game -> getScore() << std::endl;
    }
    delete game;
    return 0;
}

bool moveWorm(Board * game, char c, int numRows, int numCols) {
    if (game -> getMunchieCountdown() > 0) {
        return game -> growWorm(c);
    } else {
        return game -> moveWorm(c);
    }


    // Board::coord head;
    // head.x = game -> getCurrent().x;
    // head.y = game -> getCurrent().y;
    //
    // // Move the head
    // if (game -> getPrevious().x != 0 && game -> getPrevious().y != 0) {
    //     displayChar(game -> getPrevious().x, game -> getPrevious().y, ' ');
    //     displayChar(game -> getCurrent().x, game -> getCurrent().y, '@');
    //     refresh();
    // }
    //
    //
    // // Update the free pool
    // // game -> removeFromFree(game -> getCurrent().x, game -> getCurrent().y);
    // // game -> addToFree(game -> getPrevious().x, game -> getPrevious().y);
    //
    // // Update the previous position
    // game -> getPrevious().x = game -> getCurrent().x;
    // game -> getPrevious().y = game -> getCurrent().y;
}

void updateScore(Board * game, int numRows, int numCols) {
    std::string temp;
    temp = std::to_string(game -> getScore());
    const char * output = temp.c_str();
    mvaddstr(0, numCols -4, output);
}

void genMunchies(Board * game) {
    if (game -> getCurrent().x == game -> getMunchie().x && game -> getCurrent().y == game -> getMunchie().y) {
        game -> getMunchieCountdown() += game -> getMunchieValue();
        game -> getScore() += game -> getMunchieValue();
        game -> getMunchieValue() = 0;
        game -> isLiveMunchie() = false;
    }

    if (game -> getMunchieCountdown() > 0) {
        game -> getMunchieCountdown()--;
    }

    if (!game -> isLiveMunchie()) {
        int lastIdx = game -> getLastIdx();
        int munchieLocation = rand() % lastIdx;
        Board::coord location = game -> getCoords(munchieLocation);
        game -> getMunchie().x = location.x;
        game -> getMunchie().y = location.y;

        game -> getMunchieValue() = rand() % 8 + 1;
        char val = game -> getMunchieValue() + '0';
        displayChar(game -> getMunchie().x, game -> getMunchie().y, val);
        game -> isLiveMunchie() = true;

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

void displayChar(int x, int y, char c) {
    mvaddch(x + verticalOffset, y, c);
}
