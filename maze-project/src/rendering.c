#include <SDL2/SDL.h>
#include "rendering.h"

/**
 * draw_wall - Draws a wall on the screen.
 * @renderer: The SDL_Renderer used for rendering.
 * @x: The x position of the wall.
 * @height: The height of the wall.
 * @color: The color of the wall.
 */
void draw_wall(SDL_Renderer *renderer, int x, int height, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(renderer, x, (SCREEN_HEIGHT / 2) - (height / 2), x, (SCREEN_HEIGHT / 2) + (height / 2));
}

/**
 * draw_ground - Draws the ground on the screen.
 * @renderer: The SDL_Renderer used for rendering.
 * @color: The color of the ground.
 */
void draw_ground(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_Rect ground_rect = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &ground_rect);
}

/**
 * draw_ceiling - Draws the ceiling on the screen.
 * @renderer: The SDL_Renderer used for rendering.
 * @color: The color of the ceiling.
 */
void draw_ceiling(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_Rect ceiling_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &ceiling_rect);
}

/**
 * render_scene - Renders the entire scene including walls, ground, and ceiling.
 * @renderer: The SDL_Renderer used for rendering.
 * @walls: Array of wall heights.
 * @num_walls: Number of walls to render.
 */
void render_scene(SDL_Renderer *renderer, int *walls, int num_walls)
{
    SDL_Color wall_color_north_south = {255, 0, 0, 255}; // Red for North/South walls
    SDL_Color wall_color_east_west = {0, 0, 255, 255};   // Blue for East/West walls
    SDL_Color ground_color = {0, 255, 0, 255};           // Green for ground
    SDL_Color ceiling_color = {255, 255, 0, 255};        // Yellow for ceiling

    draw_ceiling(renderer, ceiling_color);
    draw_ground(renderer, ground_color);

    for (int i = 0; i < num_walls; i++)
    {
        SDL_Color wall_color = (i % 2 == 0) ? wall_color_north_south : wall_color_east_west;
        draw_wall(renderer, i * (SCREEN_WIDTH / num_walls), walls[i], wall_color);
    }
}