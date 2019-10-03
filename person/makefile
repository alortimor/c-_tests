CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: greeter 

greeter: person.o greeter.o
	$(CC) greeter.o person.o -o greeter 

person.o: person.cpp
	$(CC) person.cpp

greeter.o: greeter.cpp
	$(CC) $(CFLAGS) greeter.cpp

clean:
	rm *o person.o
