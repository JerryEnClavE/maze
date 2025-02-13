#include "../headers/header.h"
#include <math.h>

#define TILE_SIZE 32
#define MAP_NUM_ROWS 10
#define MAP_NUM_COLS 15
#define MINIMAP_SCALE_FACTOR 2

// Example map, using values that could represent different types of terrain
static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 0, 1, 1, 6, 0, 2, 2, 0, 1, 0, 6, 3, 0, 6},
    {6, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 6, 2, 0, 6},
    {6, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 6, 2, 3, 6},
    {6, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 6, 2, 0, 6},
    {6, 2, 0, 0, 1, 0, 0, 1, 1, 0, 0, 6, 3, 0, 6},
    {6, 0, 2, 1, 0, 0, 1, 1, 1, 0, 0, 6, 0, 1, 6},
    {6, 3, 0, 0, 0, 0, 0, 2, 1, 0, 0, 6, 0, 0, 6},
    {6, 0, 0, 2, 1, 0, 1, 0, 0, 0, 0, 6, 0, 0, 6},
    {6, 1, 1, 0, 6, 0, 1, 1, 0, 1, 0, 6, 6, 6, 6}
};

/**
 * DetectCollision - Checks if there could be a collision with the wall
 * in the player's next move.
 * @x: next x coordinate
 * @y: next y coordinate
 * Return: true if collision is detected, false otherwise
 */
bool DetectCollision(float x, float y)
{
    int mapGridX, mapGridY;

    if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE ||
            y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
        return (true);

    mapGridX = floor(x / TILE_SIZE);
    mapGridY = floor(y / TILE_SIZE);
    return (map[mapGridY][mapGridX] != 0);
}

/**
 * isInsideMap - checks if the player is still within the map boundaries
 * @x: next x coordinate
 * @y: next y coordinate
 * Return: true if inside the map, false otherwise
 */
bool isInsideMap(float x, float y)
{
    return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE &&
                y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

/**
 * getMapValue - retrieves the value of a specific cell in the map
 * @row: map row to check
 * @col: map column to check
 * Return: the value at the position in the map
 */
int getMapValue(int row, int col)
{
    return (map[row][col]);
}

/**
 * renderMap - renders the map with a hexagonal style
 */
void renderMap(void)
{
    int i, j;
    int tileX, tileY;
    color_t tileColor;

    for (i = 0; i < MAP_NUM_ROWS; i++)
    {
        for (j = 0; j < MAP_NUM_COLS; j++)
        {
            // Calculate the coordinates for the hexagonal tiles
            tileX = j * TILE_SIZE * 1.5;  // Wider horizontal offset for hexagonal cells
            tileY = i * TILE_SIZE * sqrt(3) / 2;  // Adjusted vertical offset for hexagonal cells

            // Assign a color depending on the map value
            tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

            // Draw the rectangle (or hexagon if you implement the correct shape)
            drawRect(
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tileColor
            );
        }
    }
}
