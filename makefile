# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g `sdl2-config --cflags`

# Linker flags
LDFLAGS = `sdl2-config --libs`

# Source files
SRCS = main.c raycasting.c map_parser.c player.c rendering.c textures.c enemies.c utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = maze_game

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile source files to object files
%.o: %.c maze.h
	$(CC) $(CFLAGS) -c $<

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Run the game
run: $(EXEC)
	./$(EXEC)