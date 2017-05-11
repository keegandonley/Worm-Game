# Worm Game
### CS 315 Project 5
### Keegan Donley
#### 5/9/2017

Everything works in this project as needed in the [project specifications](http://www.cs.sonoma.edu/~cs315/projects/worm/worm.pdf).
The only difference is my worm starts with the head on the left hand side instead
of on the right. Functionally, the game is playable the same way.


The worm moves in the following way:

- h: LEFT
- j: DOWN
- k: UP
- l: RIGHT

Running with no arguments `./worm.x` will use a default value of 20 x 30. The screen size can be set using
command line arguments. `./worm.x 25 40` will start a game of 25 x 40. The maximum size is 25 x 80. Anything
entered larger than that will be automatically be reduced to the maximum size.

The worm is initialized with a head and 7 body segments in the center of the screen.

Hitting yourself (the worm) or the border will cause the game to end.

The score is the combined value of 'munchies' that are picked up by moving on top of them.
