CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lSDL2 -lSDL2_image -lm

OBJ = main.o maze_utils.o

all: raycaster

raycaster: $(OBJ)
	$(CC) $(OBJ) -o raycaster $(LDFLAGS)

main.o: main.c maze_utils.h
	$(CC) $(CFLAGS) -c main.c

maze_utils.o: maze_utils.c maze_utils.h
	$(CC) $(CFLAGS) -c maze_utils.c

clean:
	rm -f *.o raycaster

