#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "raycasting.h"
#include "rendering.h"
#include "input.h"
#include "map.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Structure to represent a ray
typedef struct {
    float x;
    float y;
    float angle;      // Angle of the ray
    float distance;   // Distance to the wall
    int wallHit;      // Indicates if a wall was hit
} t_ray;

// Function to initialize raycasting
void init_raycasting(SDL_Renderer *renderer);

// Function to cast rays and detect wall intersections
void cast_rays(SDL_Renderer *renderer, float playerX, float playerY, float playerAngle);

// Function to draw walls based on raycasting results
void draw_walls(SDL_Renderer *renderer, t_ray *rays, int numRays);

// Function to clean up raycasting resources
void cleanup_raycasting();

#endif // RAYCASTING_H