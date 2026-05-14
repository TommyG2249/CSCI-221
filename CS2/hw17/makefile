CC = g++
CFLAGS = -Wall -std=c++14

hw17: hw17.o node.o
	$(CC) $(CFLAGS) hw17.o node.o -o hw17

hw17.o: hw17.cpp node.hpp
	$(CC) $(CFLAGS) -c hw17.cpp

node.o: node.cpp node.hpp
	$(CC) $(CFLAGS) -c node.cpp

clean:
	rm -f *.o hw17

submit:
	rm *.o hw17