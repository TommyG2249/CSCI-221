CC = g++
CFLAGS = -Wall -std=c++14
NCURSES = -lncurses

minesweeper: main.o cell.o mineBoard.o
	$(CC) $(CFLAGS) $(NCURSES) -o minesweeper main.o cell.o mineBoard.o

main.o: main.cpp cell.h mineBoard.h
	$(CC) $(CFLAGS) -c main.cpp

mineBoard.o: mineBoard.cpp mineBoard.h cell.h
	$(CC) $(CFLAGS) -c mineBoard.cpp

mineBoardTest: mineBoardTest.o mineBoard.o cell.o
	$(CC) $(CFLAGS) -o mineBoardTest mineBoardTest.o mineBoard.o cell.o

mineBoardTest.o: mineBoardTest.cpp mineBoard.h cell.h
	$(CC) $(CFLAGS) -c mineBoardTest.cpp
	
cellTest: cellTest.o cell.o
	$(CC) $(CFLAGS) -o cellTest cellTest.o cell.o

cellTest.o: cellTest.cpp cell.h
	$(CC) $(CFLAGS) -c cellTest.cpp

cell.o: cell.cpp cell.h
	$(CC) $(CFLAGS) -c cell.cpp

clean:
	rm *.o rm *.txt minesweeper finalPrac cellTest mineBoardTest