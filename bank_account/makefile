CC=g++
CFLAGS=-c -Wall -std=gnu++11
all: use_bank_account

use_bank_account: bank_account.o use_bank_account.o
	$(CC) use_bank_account.o bank_account.o -o use_bank_account


bank_account.o:	bank_account.cpp
	$(CC) $(CFLAGS) bank_account.cpp

use_bank_account.o: use_bank_account.cpp
	$(CC) $(CFLAGS) use_bank_account.cpp

clean:
	rm *o use_bank_account.o use_bank_account
