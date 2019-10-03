CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_tt

use_tt: tennis.o use_tt.o
	$(CC) use_tt.o tennis.o -o use_tt


tennis.o:	tennis.cpp
	$(CC) $(CFLAGS) tennis.cpp

use_tt.o: use_tt.cpp
	$(CC) $(CFLAGS) use_tt.cpp

clean:
	rm *o use_tt.o use_tt
