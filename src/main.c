#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include "../include/map.h"
#include "../include/player.h"
#include "../include/minimap.h"
#include "../include/textures.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV 60.0
#define NUM_RAYS SCREEN_WIDTH

SDL_Texture* wall_texture = NULL;

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

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_Rect ceiling_rect = {i, 0, 1, (SCREEN_HEIGHT / 2) - (line_height / 2)};
        SDL_RenderFillRect(renderer, &ceiling_rect);

        if (wall_texture) {
            SDL_Rect wall_rect = {i, (SCREEN_HEIGHT / 2) - (line_height / 2), 1, line_height};
            SDL_RenderCopy(renderer, wall_texture, NULL, &wall_rect);
        }

        SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
        SDL_Rect floor_rect = {i, (SCREEN_HEIGHT / 2) + (line_height / 2), 1, line_height};
        SDL_RenderFillRect(renderer, &floor_rect);

        ray_angle += FOV / NUM_RAYS;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycasting con Texturas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    wall_texture = load_texture("assets/wall_texture.bmp", renderer);
    if (!wall_texture) {
        printf("Error al cargar la textura de la pared.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player = {200, 200, 90};
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        handle_input(keys, &player);

        SDL_RenderClear(renderer);
        cast_rays(renderer, &player);
        draw_minimap(renderer, &player);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(wall_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
