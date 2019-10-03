CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: usestok01 

usestok01: stock00.o usestok01.o
	$(CC) usestok01.o stock00.o -o usestok01

stock00.o: stock00.cpp
	$(CC) $(CFLAGS) stock00.cpp

usestok01.o: usestok01.cpp
	$(CC) $(CFLAGS) usestok01.cpp

clean:
	rm *o usestok.o
