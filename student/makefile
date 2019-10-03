CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_student 

use_student: student.o use_student.o
	$(CC) use_student.o student.o -o use_student

student.o: student.cpp
	$(CC) $(CFLAGS) student.cpp

use_student.o: use_student.cpp
	$(CC) $(CFLAGS) use_student.cpp

clean:
	rm *o use_student
