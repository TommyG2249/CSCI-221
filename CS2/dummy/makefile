CC = g++
CFLAGS = -Wall -std=c++14
NCURSES = -lncurses

twoDArray: twoDArray.o 
	$(CC) $(CFLAGS) twoDArray.o -o twoDArray

twoDArray.o: twoDArray.cpp
	$(CC) $(CFLAGS) -c twoDArray.cpp

clean:
	rm *.o twoDArray