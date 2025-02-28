#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 60

void init_SDL(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    
    *window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(1);
    }
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_map(SDL_Renderer *renderer) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 1) {
                SDL_Rect rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco para las paredes
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    init_SDL(&window, &renderer);
    
    int running = 1;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        render_map(renderer);
        
        SDL_RenderPresent(renderer);
    }
    
    cleanup(window, renderer);
    return 0;
}
