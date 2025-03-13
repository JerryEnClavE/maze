#include <SDL2/SDL.h>
#include "../inc/minimap.h"
#include "../inc/player.h"
#include "../inc/map.h"  // Asegúrate de que este archivo define MAP_HEIGHT, MAP_WIDTH, TILE_SIZE, MINIMAP_SCALE, y map

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
}
