#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"
#include "minimap.h"

#define MINIMAP_SCALE 0.2

void draw_minimap(SDL_Renderer* renderer, Player* player) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile_rect = {
                x * TILE_SIZE * MINIMAP_SCALE,
                y * TILE_SIZE * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE,
                TILE_SIZE * MINIMAP_SCALE
            };
            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for walls
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for empty space
            }
            SDL_RenderFillRect(renderer, &tile_rect);
        }
    }

    // Draw player on minimap
    SDL_Rect player_rect = {
        player->x * MINIMAP_SCALE - 2,
        player->y * MINIMAP_SCALE - 2,
        4,
        4
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for player
    SDL_RenderFillRect(renderer, &player_rect);
}