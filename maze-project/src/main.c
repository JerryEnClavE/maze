#include <SDL2/SDL.h>
#include <stdio.h>
#include "raycasting.h"
#include "rendering.h"
#include "input.h"
#include "map.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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
        cast_rays(renderer);
        render_scene(renderer);

        // Present the back buffer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}