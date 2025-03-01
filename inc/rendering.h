// rendering.h
#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>

// Function to initialize rendering
void init_rendering(SDL_Renderer **renderer, SDL_Window *window);

// Function to draw walls based on raycasting results
void draw_walls(SDL_Renderer *renderer, int **map, int map_width, int map_height, float camera_angle);

// Function to draw the ground and ceiling
void draw_ground_ceiling(SDL_Renderer *renderer, int screen_width, int screen_height);

// Function to load textures for walls, ground, and ceiling
int load_textures(SDL_Renderer *renderer);

// Function to free textures
void free_textures();

#endif // RENDERING_H