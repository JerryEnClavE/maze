CC = gcc
CFLAGS = -std=c17 -I/usr/include/SDL2
LDFLAGS = -lSDL2

all: ProyectMaze

ProyectMaze: main.o
    $(CC) -o ProyectMaze main.o $(LDFLAGS)

main.o: main.c
    $(CC) $(CFLAGS) -c main.c

clean:
    rm -f ProyectMaze main.o
