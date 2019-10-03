CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: stacker 

stacker: stack.o stacker.o
	$(CC) stacker.o stack.o -o stacker

stack.o: stack.cpp
	$(CC) $(CFLAGS) stack.cpp

stacker.o: stacker.cpp
	$(CC) $(CFLAGS) stacker.cpp

clean:
	rm *o stacker.o
