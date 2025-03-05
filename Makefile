CC = gcc
CFLAGS = `sdl2-config --cflags` -Wall -Wextra -g
LDFLAGS = `sdl2-config --libs`

SRC = main.c map.c minimap.c player.c textures.c
OBJ = $(SRC:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
