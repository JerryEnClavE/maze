CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=gnu89 -pedantic
SRC = src/main.c src/raycasting.c src/rendering.c src/input.c src/map.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = maze_game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lSDL2

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re