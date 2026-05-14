CC = g++
CFLAGS = -Wall -std=c++14

hw22: hw22.o bst.o btnode.o
	$(CC) $(CFLAGS) -o hw22 hw22.o bst.o btnode.o
	
hw22.o: hw22.cpp bst.hpp btnode.hpp
	$(CC) $(CFLAGS) -c hw22.cpp

bst_test: bst_driver.o bst.o btnode.o btnode.hpp
	$(CC) $(CFLAGS) -o bst_test bst_driver.o bst.o btnode.o
	
bst_driver.o: bst_driver.cpp bst.hpp btnode.hpp
	$(CC) $(CFLAGS) -c bst_driver.cpp
	
bst.o: bst.cpp bst.hpp btnode.hpp
	$(CC) $(CFLAGS) -c bst.cpp	
	
btnode.o: btnode.cpp btnode.hpp
	$(CC) $(CFLAGS) -c btnode.cpp
	
clean:
	rm *.o bst_test hw22 *.csv