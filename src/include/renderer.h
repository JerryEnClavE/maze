#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "player.h"

void draw_3d_view(SDL_Renderer* renderer, Player* player);
void draw_minimap(SDL_Renderer* renderer, Player* player);

#endif // RENDERER_H