CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: keepscore 

keepscore: golf.o keepscore.o
	$(CC) keepscore.o golf.o -o keepscore 

golf.o: golf.cpp
	$(CC) golf.cpp

keepscore.o: keepscore.cpp
	$(CC) $(CFLAGS) keepscore.cpp

clean:
	rm *o golf.o
