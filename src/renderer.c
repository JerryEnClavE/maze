#include <SDL2/SDL.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "include/renderer.h"
#include "include/player.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MAP_SIZE 15
#define TILE_SIZE 32
#define FOV 90.0
#define NUM_RAYS (SCREEN_WIDTH/2)
#define WALL_HEIGHT 32.0
#define PROJECTION_PLANE ((SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * M_PI / 180.0))
#define WALL_SLICE_WIDTH 2

int map[MAP_SIZE][MAP_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void draw_3d_view(SDL_Renderer* renderer, Player* player) {
    float ray_angle = player->angle - FOV/2;
    float ray_angle_step = FOV / NUM_RAYS;

    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_Rect sky = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 0.65};
    SDL_RenderFillRect(renderer, &sky);

    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_Rect floor = {0, SCREEN_HEIGHT * 0.65, SCREEN_WIDTH, SCREEN_HEIGHT * 0.35};
    SDL_RenderFillRect(renderer, &floor);

    for (int i = 0; i < NUM_RAYS; i++) {
        float rad = ray_angle * M_PI / 180.0;
        float ray_x = player->x;
        float ray_y = player->y;
        float sin_a = sin(rad);
        float cos_a = cos(rad);
        float distance = 0;
        int hit_wall = 0;
        int wall_type = 0;

        float step_size = 0.02;
        while (!hit_wall && distance < 40) {
            ray_x += cos_a * step_size;
            ray_y += sin_a * step_size;
            distance += step_size;

            int map_x = (int)ray_x;
            int map_y = (int)ray_y;

            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] > 0) {
                    hit_wall = 1;
                    wall_type = map[map_y][map_x];
                }
            }
        }

        float ca = player->angle - ray_angle;
        if (ca < 0) ca += 360;
        if (ca >= 360) ca -= 360;
        distance = distance * cos(ca * M_PI / 180.0);

        float wall_height = (WALL_HEIGHT * PROJECTION_PLANE) / (distance + 0.0001);
        
        int wall_top = (SCREEN_HEIGHT - wall_height) / 2;
        int wall_bottom = (SCREEN_HEIGHT + wall_height) / 2;
        
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= SCREEN_HEIGHT) wall_bottom = SCREEN_HEIGHT - 1;

        int r = 0, g = 0, b = 255;

        int shade = 255 - (int)(distance * 2);
        if (shade < 60) shade = 60;
        if (shade > 255) shade = 255;

        SDL_Rect wall_slice = {
            i * WALL_SLICE_WIDTH,
            wall_top,
            WALL_SLICE_WIDTH,
            wall_bottom - wall_top
        };
        SDL_SetRenderDrawColor(renderer, r * shade / 255, g * shade / 255, b * shade / 255, 255);
        SDL_RenderFillRect(renderer, &wall_slice);

        ray_angle += ray_angle_step;
    }
}

void draw_minimap(SDL_Renderer* renderer, Player* player) {
    int minimap_size = 150;
    float scale = (float)minimap_size / (MAP_SIZE * TILE_SIZE);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_Rect minimap_bg = {0, 0, minimap_size, minimap_size};
    SDL_RenderFillRect(renderer, &minimap_bg);

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            SDL_Rect tile = {
                x * TILE_SIZE * scale,
                y * TILE_SIZE * scale,
                TILE_SIZE * scale - 1,
                TILE_SIZE * scale - 1
            };

            if (map[y][x] > 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 128);
            } else {
                SDL_SetRenderDrawColor(renderer, 40, 40, 40, 128);
            }
            SDL_RenderFillRect(renderer, &tile);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect player_dot = {
        player->x * TILE_SIZE * scale - 2,
        player->y * TILE_SIZE * scale - 2,
        4,
        4
    };
    SDL_RenderFillRect(renderer, &player_dot);

    float dir_x = player->x * TILE_SIZE * scale + cos(player->angle * M_PI / 180.0) * 10;
    float dir_y = player->y * TILE_SIZE * scale + sin(player->angle * M_PI / 180.0) * 10;
    SDL_RenderDrawLine(renderer,
        player->x * TILE_SIZE * scale,
        player->y * TILE_SIZE * scale,
        dir_x,
        dir_y
    );
}