CC = g++
CFLAGS = -Wall -std=c++14

hw21: hw21.o btnode.o
	$(CC) $(CFLAGS) -o hw21 hw21.o btnode.o

hw21.o: hw21.cpp btnode.hpp
	$(CC) $(CFLAGS) -c hw21.cpp

btnode.o: btnode.cpp btnode.hpp
	$(CC) $(CFLAGS) -c btnode.cpp
	
clean:
	rm *.o hw21