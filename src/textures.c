#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "map.h"

SDL_Texture* floor_texture = NULL;
SDL_Texture* ceiling_texture = NULL;
SDL_Texture* wall_texture = NULL;

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
if (!surface) {
    printf("Error loading image %s: %s\n", path,
           SDL_GetError());
}
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
SDL_FreeSurface(surface);
if (texture) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
}
return texture;
}
