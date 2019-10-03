CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: time_usage

time_usage: time.o time_usage.o
	$(CC) time_usage.o time.o -o time_usage


time.o:	time.cpp
	$(CC) $(CFLAGS) time.cpp

time_usage.o: time_usage.cpp
	$(CC) $(CFLAGS) time_usage.cpp

clean:
	rm *o time_usage.o timeusage
