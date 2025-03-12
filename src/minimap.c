#include <SDL2/SDL.h>
#include "../inc/map.h"
#include "../inc/player.h"
#include "../inc/minimap.h"
#include "../inc/enemy.h"

#define MINIMAP_SCALE 0.2

void draw_minimap(SDL_Renderer* renderer, Player* player, Enemy* enemies, int num_enemies) {
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

    // Dibujar a los enemigos en el minimapa (puntos rojos)
    for (int i = 0; i < num_enemies; i++) {
        SDL_Rect enemy_rect = {
            (int)(enemies[i].x * MINIMAP_SCALE) - 2,
            (int)(enemies[i].y * MINIMAP_SCALE) - 2,
            4,
            4
        };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo para los enemigos
        SDL_RenderFillRect(renderer, &enemy_rect);
    }
}
