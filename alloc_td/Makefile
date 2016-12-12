CC = g++
CFLAGS=-std=c++11 -ansi -pedantic -Wall -Wextra
LFLAGS=
EXEC = image.exe
SRC:=$(shell find . -type f -name '*.cpp')
HEADERS:=$(shell find . -type f -name '*.h')

all: $(EXEC)

image.exe: $(SRC) $(HEADERS)
	$(CC) $(SRC) $(CFLAGS) -o $(EXEC)

clean:
	rm -rf *.o $(EXEC)