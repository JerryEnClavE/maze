CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lupng -lm

SOURCES = $(wildcard ./src/*.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = Proyect-Maze

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

