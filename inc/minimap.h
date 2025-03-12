#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL2/SDL.h>
#include "player.h"
#include "enemy.h"

void draw_minimap(SDL_Renderer* renderer, Player* player, Enemy* enemies, int num_enemies);

#endif