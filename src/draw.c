#include "../headers/header.h"

/**
 * drawRect - draw a rectangle
 * @x: x coordinate
 * @y: y coordinate
 * @width: rectangle width
 * @height: rectangle height
 * @color: pixel color
*/
void drawRect(int x, int y, int width, int height, color_t color)
{
    int i, j;
    int maxX = x + width;
    int maxY = y + height;

    for (i = x; i <= maxX; i++)
    {
        for (j = y; j <= maxY; j++)
        {
            drawPixel(i, j, color);
        }
    }
}

/**
 * drawLine - draw a line using Bresenham's algorithm
 * @x0: x coordinate init
 * @y0: y coordinate init
 * @x1: x coordinate end
 * @y1: y coordinate end
 * @color: pixel color
*/
void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        drawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}