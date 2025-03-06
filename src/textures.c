#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Texture* floor_texture = NULL;
SDL_Texture* ceiling_texture = NULL;
SDL_Texture* wall_texture = NULL;

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("Failed to load texture: %s\n", IMG_GetError());
        return NULL;
    }
    return texture;
}