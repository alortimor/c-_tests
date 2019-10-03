CC=g++
CFLAGS=-c -Wall -std=c++11
all: use_shoe 

use_shoe: shoe.o use_shoe.o
	$(CC) use_shoe.o shoe.o -o use_shoe

shoe.o: shoe.cpp
	$(CC) $(CFLAGS) shoe.cpp

use_shoe.o: use_shoe.cpp
	$(CC) $(CFLAGS) use_shoe.cpp

clean:
	rm *o use_shoe
