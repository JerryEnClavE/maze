#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL2/SDL.h>
#include "player.h"

void draw_minimap(SDL_Renderer* renderer, Player* player);

#endif // MINIMAP_H