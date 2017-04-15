CC = gcc
CFLAGS=-c -Wall -Wextra 
LFLAGS=-shared -ldl -g
EXEC = libfunc.so

all: $(EXEC) clean

libfunc.so: func.o 
	$(CC) func.o $(LFLAGS) -o $@

func.o: func.cpp fonction.h 
	gcc $(CFLAGS) -o func.o -fpic func.cpp

clean:
	rm -rf *.o