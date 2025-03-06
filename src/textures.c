#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file) {
    if (!renderer || !file) {
        printf("Renderer or file is NULL\n");
        return NULL;
    }

    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    if (!texture) {
        printf("Failed to load texture %s! SDL_image Error: %s\n", file, IMG_GetError());
    }
    return texture;
}