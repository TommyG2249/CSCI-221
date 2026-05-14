CC = g++
CFLAGS = -Wall -std=c++14
NCURSES = -lncurses

nprac: prac.o 
	$(CC) $(CFLAGS) prac.o -o nprac $(NCURSES)

prac.o: prac.cpp
	$(CC) $(CFLAGS) -c prac.cpp

clean:
	rm *.o nprac