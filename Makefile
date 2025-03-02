# Variables
CC = gcc
CFLAGS = -I../include -Wall -g
LDFLAGS = -lSDL2
SRC = src/input.c src/other_source_files.c
OBJ = $(SRC:.c=.o)
TARGET = maze

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(TARGET)