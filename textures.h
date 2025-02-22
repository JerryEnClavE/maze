#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

extern SDL_Texture* floor_texture;
extern SDL_Texture* ceiling_texture;
extern SDL_Texture* wall_texture;

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path);

#endif // TEXTURES_H