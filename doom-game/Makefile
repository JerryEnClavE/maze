CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=gnu89 -pedantic
LDFLAGS = -lSDL2 -lSDL2_image

SRC = src/main.c src/game.c src/player.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = doom_game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean