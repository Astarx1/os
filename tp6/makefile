CC = gcc
# -L./ -lfunc
CFLAGS=-Wall -Wextra -lpthread -ldl -rdynamic
LFLAGS=
EXEC = concur_tp.exe

all: $(EXEC)

concur_tp.exe: main.cpp fonction.h
	$(CC) main.cpp $(CFLAGS) -o $@

clean:
	rm -rf *.o $(EXEC)