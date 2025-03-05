#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include "map.h"
#include "player.h"
#include "minimap.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV 60.0
#define NUM_RAYS SCREEN_WIDTH

void cast_rays(SDL_Renderer* renderer, Player* player) {
    float ray_angle = player->angle - (FOV / 2);
    for (int i = 0; i < NUM_RAYS; i++) {
        float ray_x = player->x;
        float ray_y = player->y;
        float ray_dx = cos(ray_angle * M_PI / 180);
        float ray_dy = sin(ray_angle * M_PI / 180);
        
        while (map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] == 0) {
            ray_x += ray_dx * 2;
            ray_y += ray_dy * 2;
        }

        float distance = sqrt((ray_x - player->x) * (ray_x - player->x) +
                              (ray_y - player->y) * (ray_y - player->y));
        float corrected_dist = distance * cos((ray_angle - player->angle) * M_PI / 180);
        int line_height = (TILE_SIZE * SCREEN_HEIGHT) / corrected_dist;

        // Render ceiling (color cielo)
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Color cielo
        SDL_Rect ceiling_rect = { i, 0, 1, (SCREEN_HEIGHT / 2) - (line_height / 2) };
        SDL_RenderFillRect(renderer, &ceiling_rect);

        // Render wall (color gris)
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Color gris
        SDL_Rect wall_rect = { i, (SCREEN_HEIGHT / 2) - (line_height / 2), 1, line_height };
        SDL_RenderFillRect(renderer, &wall_rect);

        // Render floor (color verde)
        SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Color verde
        SDL_Rect floor_rect = { i, (SCREEN_HEIGHT / 2) + (line_height / 2), 1, (SCREEN_HEIGHT / 2) - (line_height / 2) };
        SDL_RenderFillRect(renderer, &floor_rect);

        ray_angle += FOV / NUM_RAYS;
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Raycasting with Colors", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Player player = {200, 200, 90};
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) running = 0;
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        handle_input(keys, &player);

        SDL_RenderClear(renderer);
        cast_rays(renderer, &player);
        draw_minimap(renderer, &player);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}