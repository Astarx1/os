CC = gcc
CFLAGS=-std=c11 -lm -L./ -lseg -ansi -pedantic -Wall -Wextra 
LFLAGS=
EXEC = td3.exe
SRC:=$(shell find . -type f -name '*.cpp') $(shell find . -type f -name '*.c')
HEADERS:=$(shell find . -type f -name '*.h')

all: $(EXEC)

td3.exe: $(SRC) $(HEADERS)
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC)

clean:
	rm -rf *.o $(EXEC)