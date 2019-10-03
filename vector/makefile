CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_vector

use_vector: vect.o use_vector.o
	$(CC) use_vector.o vect.o -o use_vector

vect.o:	vect.cpp
	$(CC) $(CFLAGS) vect.cpp

use_vector.o: use_vector.cpp
	$(CC) $(CFLAGS) use_vector.cpp

clean:
	rm *o use_vector.o use_vector
