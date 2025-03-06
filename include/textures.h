#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

SDL_Texture* load_texture(const char* file, SDL_Renderer* renderer);

#endif // TEXTURES_H