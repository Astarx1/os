CC = gcc
CFLAGS=-Wall -Wextra
LFLAGS=
EXEC = exec_tp.exe

all: $(EXEC)

exec_tp.exe: main.c func.h shell.h
	$(CC) main.c $(CFLAGS) -o $@

clean:
	rm -rf *.o $(EXEC)