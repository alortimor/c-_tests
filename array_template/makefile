CC=g++
CFLAGS=-c -Wall -std=c++11
all: stacker 

stacker: stack.o stacker.o
	$(CC) stacker.o stack.o -o stacker

stack.o: stack.cpp
	$(CC) $(CFLAGS) stack.cpp

stacker.o: stacker.cpp
	$(CC) $(CFLAGS) stacker.cpp

clean:
	rm *o stacker
