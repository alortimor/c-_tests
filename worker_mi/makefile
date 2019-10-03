CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_worker 

use_worker: worker.o use_worker.o
	$(CC) use_worker.o worker.o -o use_worker

worker.o: worker.cpp
	$(CC) $(CFLAGS) worker.cpp

use_worker.o: use_worker.cpp
	$(CC) $(CFLAGS) use_worker.cpp

clean:
	rm *o use_worker
