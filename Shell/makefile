CC = g++
CFLAGS=-std=c++11 -ansi -pedantic -Wall -Wextra
LFLAGS=
EXEC = fork.exe
SRC:=$(shell find . -type f -name '*.cpp')
HEADERS:=$(shell find . -type f -name '*.h')

all: $(EXEC)

fork.exe: $(SRC) $(HEADERS)
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC)

clean:
	rm -rf *.o $(EXEC)