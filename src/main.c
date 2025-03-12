#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../inc/map.h"
#include "../inc/player.h"
#include "../inc/textures.h"
#include "../inc/minimap.h"
#include "../inc/enemy.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV 60.0
#define NUM_RAYS SCREEN_WIDTH
#define TILE_SIZE 64
#define MAX_ENEMIES 10

SDL_Texture* wall_texture = NULL;

void cast_rays(SDL_Renderer* renderer, Player* player) {
    if (!renderer || !player) {
        printf("Renderer or player is NULL\n");
        return;
    }

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

        // Calculate the exact position of the texture on the wall
        int texture_offset_x = (int)(ray_x) % TILE_SIZE;
        SDL_Rect src_rect = { texture_offset_x, 0, 1, TILE_SIZE };
        SDL_Rect dst_rect = { i, (SCREEN_HEIGHT / 2) - (line_height / 2), 1, line_height };

        // Render ceiling
        SDL_Rect ceiling_rect = { i, 0, 1, (SCREEN_HEIGHT / 2) - (line_height / 2) };
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Color clear
        SDL_RenderFillRect(renderer, &ceiling_rect);

        // Render wall with adjusted texture
        if (wall_texture) {
            SDL_RenderCopy(renderer, wall_texture, &src_rect, &dst_rect);
        } else {
            printf("Wall texture is NULL\n");
        }

        // Render floor
        SDL_Rect floor_rect = { i, (SCREEN_HEIGHT / 2) + (line_height / 2), 1, (SCREEN_HEIGHT / 2) - (line_height / 2) };
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Color marron
        SDL_RenderFillRect(renderer, &floor_rect);

        ray_angle += FOV / NUM_RAYS;
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycasting with Textures", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    wall_texture = load_texture(renderer, "textures/wall.png");
    if (!wall_texture) {
        printf("Failed to load wall texture\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* enemy_texture = load_texture(renderer, "textures/enemy.png");
    if (!enemy_texture) {
        printf("Failed to load enemy texture\n");
        SDL_DestroyTexture(wall_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player = {200, 200, 90};
    int num_enemies = MAX_ENEMIES;
    Enemy enemies[MAX_ENEMIES];

    for (int i = 0; i < num_enemies; i++) {
        init_enemy(&enemies[i], 100.0f, 100.0f, 0.0f, enemy_texture); // Example initial positions and angle
    }

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

        for (int i = 0; i < num_enemies; i++) {
            update_enemy(&enemies[i], &player);
        }

        SDL_RenderClear(renderer);
        cast_rays(renderer, &player);
        draw_minimap(renderer, &player, enemies, num_enemies);  // Pasamos los enemigos aquí
        for (int i = 0; i < num_enemies; i++) {
            render_enemy(renderer, &enemies[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(enemy_texture);
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
