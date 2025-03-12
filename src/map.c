#include "../inc/map.h"
#include "../inc/enemy.h"

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Define the positions of the enemies in the map
Enemy enemies[] = {
    {128, 128, 0, NULL}, // Example positions
    {256, 128, 0, NULL},
    {384, 128, 0, NULL},
    {512, 128, 0, NULL},
    {640, 128, 0, NULL}
};
int num_enemies = sizeof(enemies) / sizeof(enemies[0]);