CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: track_score

track_score: linked_list.o track_score.o
	$(CC) track_score.o linked_list.o -o track_score

linked_list.o: linked_list.cpp
	$(CC) $(CFLAGS) linked_list.cpp

track_score.o: track_score.cpp
	$(CC) $(CFLAGS) track_score.cpp

clean:
	rm *o track_score.o
