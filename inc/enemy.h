#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include "player.h"

typedef struct {
    float x, y;
    float angle;
    SDL_Texture* texture;
} Enemy;

void init_enemy(Enemy* enemy, float x, float y, float angle, SDL_Texture* texture);
void update_enemy(Enemy* enemy, Player* player);
void render_enemy(SDL_Renderer* renderer, Enemy* enemy);

#endif