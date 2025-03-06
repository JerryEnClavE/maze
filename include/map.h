#ifndef MAP_H
#define MAP_H

#define TILE_SIZE 64

extern int **map;

char **load_map(const char *filename);

#endif