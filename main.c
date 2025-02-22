#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include "map.h"
#include "player.h"
#include "textures.h"
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

        // Calcular la posición exacta de la textura en la pared
        int texture_offset_x = (int)(ray_x) % TILE_SIZE;
        SDL_Rect src_rect = { texture_offset_x, 0, 1, TILE_SIZE };
        SDL_Rect dst_rect = { i, (SCREEN_HEIGHT / 2) - (line_height / 2), 1, line_height };

        // Renderizar techo
        SDL_Rect ceiling_rect = { i, 0, 1, (SCREEN_HEIGHT / 2) - (line_height / 2) };
        SDL_RenderCopy(renderer, ceiling_texture, NULL, &ceiling_rect);

        // Renderizar pared con textura ajustada
        SDL_RenderCopy(renderer, wall_texture, &src_rect, &dst_rect);

        // Renderizar piso
        SDL_Rect floor_rect = { i, (SCREEN_HEIGHT / 2) + (line_height / 2), 1, (SCREEN_HEIGHT / 2) - (line_height / 2) };
        SDL_RenderCopy(renderer, floor_texture, NULL, &floor_rect);

        ray_angle += FOV / NUM_RAYS;
    }
}

void handle_input(const Uint8* keys, Player* player) {
    float move_speed = 5.0;
    float rotate_speed = 3.0;
    float new_x = player->x;
    float new_y = player->y;

    if (keys[SDL_SCANCODE_W]) {
        new_x += cos(player->angle * M_PI / 180) * move_speed;
        new_y += sin(player->angle * M_PI / 180) * move_speed;
    }
    if (keys[SDL_SCANCODE_S]) {
        new_x -= cos(player->angle * M_PI / 180) * move_speed;
        new_y -= sin(player->angle * M_PI / 180) * move_speed;
    }
    if (map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0) {
        player->x = new_x;
        player->y = new_y;
    }

    if (keys[SDL_SCANCODE_A]) player->angle -= rotate_speed;
    if (keys[SDL_SCANCODE_D]) player->angle += rotate_speed;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Raycasting with Textures", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    floor_texture = load_texture(renderer, "textures/floor.png");
    ceiling_texture = load_texture(renderer, "textures/ceiling.png");
    wall_texture = load_texture(renderer, "textures/wall.png");

    if (!floor_texture || !ceiling_texture || !wall_texture) {
        printf("Error loading textures\n");
        return 1;
    }

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

    SDL_DestroyTexture(floor_texture);
    SDL_DestroyTexture(ceiling_texture);
    SDL_DestroyTexture(wall_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}