CC=g++
CFLAGS=-c -Wall -std=c++11
all: passgen

passgen: passgen.o pwgen_fn.o
		$(CC) passgen.o pwgen_fn.o -o passgen 

pwgen_fn.o: pwgen_fn.cpp
		$(CC) $(CFLAGS) pwgen_fn.cpp

passgen.o: passgen.cpp
		$(CC) $(CFLAGS) passgen.cpp

clean:
		rm *o passgen.o



