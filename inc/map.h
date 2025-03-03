#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct s_map {
    int layout[MAP_HEIGHT][MAP_WIDTH];
} t_map;

/**
 * Initializes the map with default values.
 * @param map Pointer to the map structure to initialize.
 */
void init_map(t_map *map);

/**
 * Loads a map from a specified file.
 * @param filename The path to the map file.
 * @return A pointer to the loaded map, or NULL on failure.
 */
char **load_map(const char *filename);

/**
 * Frees any resources associated with the map.
 * @param map Pointer to the map structure to free.
 */
void free_map(char **map, size_t line_count);

/**
 * Prints the map layout to the console for debugging purposes.
 * @param map Pointer to the map structure to print.
 */
void print_map(char **map, size_t line_count);

#endif /* MAP_H */