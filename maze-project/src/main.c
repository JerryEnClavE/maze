#include <SDL2/SDL.h>
#include <stdio.h>
#include "raycasting.h"

// Define the Ray structure
typedef struct {
    float x;
    float y;
    float angle;
    float distance;
} Ray;
#include "rendering.h"
#include "input.h"
#include "map.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void cast_rays(SDL_Renderer *renderer, float player_x, float player_y, float angle, int **map, int map_width, int map_height, Ray *rays, int num_rays);

int main(void)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int running = 1;
    SDL_Event event;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create the window
    window = SDL_CreateWindow("Maze Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Define other necessary variables
    float player_x = 0.0f, player_y = 0.0f, angle = 0.0f;
    int **map = NULL; // Initialize your map appropriately
    int map_width = 0, map_height = 0; // Set your map dimensions
    Ray *rays = NULL; // Initialize your rays array appropriately
    int num_rays = 0; // Set the number of rays
    int *walls = NULL; // Initialize your walls array appropriately
    int num_walls = 0; // Set the number of walls

    // Main game loop
    while (running)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            handle_input(event);
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Perform raycasting and rendering
        cast_rays(renderer, player_x, player_y, angle, map, map_width, map_height, rays, num_rays);
        render_scene(renderer, walls, num_walls);

        // Present the back buffer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}