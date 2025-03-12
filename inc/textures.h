#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file);

#endif // TEXTURES_H