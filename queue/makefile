CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_queue

use_queue: queue.o use_queue.o
	$(CC) use_queue.o queue.o -o use_queue


queue.o:	queue.cpp
	$(CC) $(CFLAGS) queue.cpp

use_queue.o: use_queue.cpp
	$(CC) $(CFLAGS) use_queue.cpp

clean:
	rm *o use_queue.o use_queue
