CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: convert_stone

convert_stone: stonewt.o convert_stone.o
	$(CC) convert_stone.o stonewt.o -o convert_stone

stonewt.o:	stonewt.cpp
	$(CC) $(CFLAGS) stonewt.cpp

convert_stone.o: convert_stone.cpp
	$(CC) $(CFLAGS) convert_stone.cpp

clean:
	rm *o convert_stone.o convert_stone
