CC = g++
CFLAGS = -Wall -std=c++14

hw20: hw20.o btnode.o
	$(CC) $(CFLAGS) -o hw20 hw20.o btnode.o

hw20.o: hw20.cpp btnode.hpp
	$(CC) $(CFLAGS) -c hw20.cpp

btnode.o: btnode.cpp btnode.hpp
	$(CC) $(CFLAGS) -c btnode.cpp
	
clean:
	rm *.o hw20