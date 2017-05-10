worm.x:  screen.o getChar.o board.o
	g++ -ggdb -o worm.x screen.o getChar.o board.o -lcurses -ltermcap

screen.o: screen.cpp board.cpp board.hpp directions.hpp move.hpp
	g++ -std=c++11 -c -ggdb screen.cpp -o screen.o

getChar.o: getChar.cpp getChar.hpp directions.hpp
	gcc -c -ggdb getChar.cpp -o getChar.o

board.o: board.cpp board.hpp move.hpp directions.hpp
	gcc -c -ggdb board.cpp -o board.o

clean:
	/bin/rm -f *.x *.o *~

run:
	make worm.x
	./worm.x 25 80
