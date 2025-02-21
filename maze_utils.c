#include "maze_utils.h"
#include <math.h>
#include <stdio.h>

#define TILE_SIZE 64
#define FOV 60
#define NUM_RAYS 800
#define SCREEN_HEIGHT 600

extern int map[10][10];  // Mapa definido en main.c

SDL_Texture* wallTexture = NULL;
SDL_Texture* ceilingTexture = NULL;
SDL_Texture* floorTexture = NULL;

void load_textures(SDL_Renderer* renderer) {
    wallTexture = IMG_LoadTexture(renderer, "wall.png");
    ceilingTexture = IMG_LoadTexture(renderer, "ceiling.png");
    floorTexture = IMG_LoadTexture(renderer, "floor.png");

    if (!wallTexture) {
        printf("Error cargando la textura de la pared: %s\n", IMG_GetError());
    }
    if (!ceilingTexture) {
        printf("Error cargando la textura del techo: %s\n", IMG_GetError());
    }
    if (!floorTexture) {
        printf("Error cargando la textura del suelo: %s\n", IMG_GetError());
    }
}

void free_textures() {
    if (wallTexture) {
        SDL_DestroyTexture(wallTexture);
        wallTexture = NULL;
    }
    if (ceilingTexture) {
        SDL_DestroyTexture(ceilingTexture);
        ceilingTexture = NULL;
    }
    if (floorTexture) {
        SDL_DestroyTexture(floorTexture);
        floorTexture = NULL;
    }
}

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

        SDL_Rect wallRect = {i, (SCREEN_HEIGHT / 2) - (line_height / 2), 1, line_height};
        SDL_Rect ceilingRect = {i, 0, 1, (SCREEN_HEIGHT / 2) - (line_height / 2)};
        SDL_Rect floorRect = {i, (SCREEN_HEIGHT / 2) + (line_height / 2), 1, SCREEN_HEIGHT - (SCREEN_HEIGHT / 2) - (line_height / 2)};

        if (ceilingTexture) {
            SDL_RenderCopy(renderer, ceilingTexture, NULL, &ceilingRect);
        } else {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawLine(renderer, i, ceilingRect.y, i, ceilingRect.y + ceilingRect.h);
        }

        if (floorTexture) {
            SDL_RenderCopy(renderer, floorTexture, NULL, &floorRect);
        } else {
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderDrawLine(renderer, i, floorRect.y, i, floorRect.y + floorRect.h);
        }

        if (wallTexture) {
            SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, i, wallRect.y, i, wallRect.y + wallRect.h);
        }

        ray_angle += (float)FOV / NUM_RAYS;
    }
}
