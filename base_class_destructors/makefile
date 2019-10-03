CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: usedma

usedma: dma.o usedma.o
	$(CC) usedma.o dma.o -o usedma


dma.o:	dma.cpp
	$(CC) $(CFLAGS) dma.cpp

usedma.o: usedma.cpp
	$(CC) $(CFLAGS) usedma.cpp

clean:
	rm *o usedma.o usedma
