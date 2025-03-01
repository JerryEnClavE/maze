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
 * @param map Pointer to the map structure to load data into.
 * @param filename The path to the map file.
 * @return 1 on success, 0 on failure.
 */
int load_map(t_map *map, const char *filename);

/**
 * Frees any resources associated with the map.
 * @param map Pointer to the map structure to free.
 */
void free_map(t_map *map);

/**
 * Prints the map layout to the console for debugging purposes.
 * @param map Pointer to the map structure to print.
 */
void print_map(const t_map *map);

#endif /* MAP_H */