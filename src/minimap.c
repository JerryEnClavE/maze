#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../inc/map.h"
#include "../inc/player.h"
#include "../inc/textures.h"
#include "../inc/minimap.h"
#include "../inc/config.h"  // Include the new config header file

void draw_minimap(SDL_Renderer* renderer, Player* player) { 
    // Dibujar el mapa
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile_rect = {
                x * TILE_SIZE * MINIMAP_SCALE,
                y * TILE_SIZE * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE
            };
            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco para las paredes
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro para el espacio vacío
            }
            SDL_RenderFillRect(renderer, &tile_rect);
        }
    }

    // Dibujar al jugador en el minimapa (punto verde)
    SDL_Rect player_rect = {
        (int)(player->x * MINIMAP_SCALE) - 2,
        (int)(player->y * MINIMAP_SCALE) - 2,
        4,
        4
    };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde para el jugador
    SDL_RenderFillRect(renderer, &player_rect);

    // Dibujar los rayos de visión en el minimapa
    float ray_angle = player->angle - (FOV / 2);
    for (int i = 0; i < NUM_RAYS; i++) {
        float ray_x = player->x;
        float ray_y = player->y;
        float ray_dx = cos(ray_angle * M_PI / 180);
        float ray_dy = sin(ray_angle * M_PI / 180);
        
        int hit = 0;
        while (!hit) {
            if (map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] == 1) {
                hit = 1;
            } else {
                ray_x += ray_dx * 0.5; // Aumentar el tamaño del paso para extender la distancia de visualización
                ray_y += ray_dy * 0.5; // Aumentar el tamaño del paso para extender la distancia de visualización
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo para los rayos
        SDL_RenderDrawLine(renderer,
            (int)(player->x * MINIMAP_SCALE),
            (int)(player->y * MINIMAP_SCALE),
            (int)(ray_x * MINIMAP_SCALE),
            (int)(ray_y * MINIMAP_SCALE)
        );

        ray_angle += FOV / NUM_RAYS;
    }
}
