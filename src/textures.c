#include <SDL2/SDL.h>
#include "../include/textures.h"

SDL_Texture* load_texture(const char* file, SDL_Renderer* renderer) {
    SDL_Surface* surface = SDL_LoadBMP(file);
    if (!surface) {
        printf("Error al cargar la textura: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
