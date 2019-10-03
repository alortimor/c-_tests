CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: usestok0 

usestok0: stock00.o usestok0.o
	$(CC) usestok0.o stock00.o -o usestok0

stock00.o: stock00.cpp
	$(CC) $(CFLAGS) stock00.cpp

usestok0.o: usestok0.cpp
	$(CC) $(CFLAGS) usestok0.cpp

clean:
	rm *o usestok.o
