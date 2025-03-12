#include "../inc/enemy.h"
#include "../inc/player.h"
#include "../inc/map.h"
#include <math.h>
#include <SDL2/SDL.h>

void init_enemy(Enemy* enemy, float x, float y, float angle, SDL_Texture* texture) {
    enemy->x = x;
    enemy->y = y;
    enemy->angle = angle;
    enemy->texture = texture;
}

void update_enemy(Enemy* enemy, Player* player) {
    float dx = player->x - enemy->x;
    float dy = player->y - enemy->y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance > 0) {
        float new_x = enemy->x + dx / distance;
        float new_y = enemy->y + dy / distance;

        // Check for collision with walls
        if (map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0) {
            enemy->x = new_x;
            enemy->y = new_y;
        }
    }
}

void render_enemy(SDL_Renderer* renderer, Enemy* enemy) {
    SDL_Rect rect = { (int)enemy->x - 16, (int)enemy->y - 16, 32, 32 };
    if (enemy->texture) {
        SDL_RenderCopy(renderer, enemy->texture, NULL, &rect);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color rojo
        SDL_RenderFillRect(renderer, &rect);
    }
}
