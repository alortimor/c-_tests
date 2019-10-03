CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_string

use_string: string.o use_string.o
	$(CC) use_string.o string.o -o use_string


string.o:	string.cpp
	$(CC) $(CFLAGS) string.cpp

use_string.o: use_string.cpp
	$(CC) $(CFLAGS) use_string.cpp

clean:
	rm *o use_string.o use_string
