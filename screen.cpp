// Keegan Donley
// CS 315
// Project 5
// screen.cpp

// This file manges the main gameplay, as well as handling
// starting and ending curses.
#include <curses.h>
#include <cstdlib>
#include <iostream>
#include "getChar.hpp"
#include "board.hpp"
#include "directions.hpp"
#include "move.hpp"
#include <string>
#include <iomanip>


void startup( void );
void terminate( void );
void genMunchies(Board * game);
bool moveWorm(Board * game, char c, int numRows, int numCols);
void displayChar(int x, int y, char c);
void updateScore(Board * game, int numRows, int numCols);

int main(int argc, const char * argv[])
{
    int numRows = 20, numCols = 30;
    if (argc > 2) {
        numRows = atoi(argv[1]);
        numCols = atoi(argv[2]);
        if (numRows < 10 || numRows > 25 || numCols < 10 || numCols > 80) {
            numRows = 25;
            numCols = 80;
        }
    }

    // Print the * characters for the border and the title
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


    // Initialize the game board and place the character
    Board * game = new Board(numRows, numCols);
    game -> setWorm(numRows, numCols);
    bool seenMunchie = false;
    int munchieCount = 0;
    char c;

    // Generate the first munchie and render the score
    genMunchies(game);
    updateScore(game, numRows, numCols);
    refresh();

    // Continually receive input
    while ((c = get_char())) {

        // Generates a munchy whenever needed
        genMunchies(game);

        // Makes the move and validates. If the move was invalid, the loop
        // breaks and the user has lost.
        if (!moveWorm(game, c, numRows, numCols)) { break; }

        // Update display
    	updateScore(game, numRows, numCols);
        refresh();
    }
    // The game is over; the player has either lost or won
    terminate();

    // If loss, display the loss message
    if (!game -> isWin()) {
        std::cout << "You hit an obstacle!" << std::endl;
        std::cout << "Total points: " << game -> getScore() << std::endl;
    } else {
        // If win, display the win message
        std::cout << "You won!" << std::endl;
        std::cout << "Total points: " << game -> getScore() << std::endl;
    }

    delete game;
    return 0;
}

// Determines if the worm needs to move or grow
bool moveWorm(Board * game, char c, int numRows, int numCols) {
    if (game -> getMunchieCountdown() > 0) {
        return game -> growWorm(c);
    } else {
        return game -> moveWorm(c);
    }
}

// Displays the new score on-screen
void updateScore(Board * game, int numRows, int numCols) {
    std::string temp;
    temp = std::to_string(game -> getScore());
    const char * output = temp.c_str();
    mvaddstr(0, numCols -4, output);
}

// Generates a single from the free pool locations with a value of 1-9
void genMunchies(Board * game) {
    if (game -> getCurrent().x == game -> getMunchie().x && game -> getCurrent().y == game -> getMunchie().y) {
        game -> getMunchieCountdown() += game -> getMunchieValue() + 1;
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
    moveChar(x, y, c);
}
