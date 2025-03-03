#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>

// Define el tipo Ray
typedef struct {
    float x;
    float y;
    float angle;
    float distance;
} Ray;

// Define el tipo t_ray como un alias de Ray
typedef Ray t_ray;

// Declaración de la función draw_walls
void draw_walls(SDL_Renderer *renderer, t_ray *rays, int numRays);

// Declaración de la función draw_ground_ceiling
void draw_ground_ceiling(SDL_Renderer *renderer, int screen_width, int screen_height);

// Declaración de la función load_textures
int load_textures(SDL_Renderer *renderer);

// Declaración de la función free_textures
void free_textures();

#endif // RENDERING_H