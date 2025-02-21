#ifndef MAZE_UTILS_H
#define MAZE_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    float x, y;
    float angle;
} Player;

extern SDL_Texture* wallTexture;  // Textura de la pared

void cast_rays(SDL_Renderer* renderer, Player* player);
void load_textures(SDL_Renderer* renderer);
void free_textures();


extern SDL_Texture* floorTexture;  // Textura del suelo
extern SDL_Texture* ceilingTexture;  // Textura del techo
extern SDL_Texture* playerTexture;  // Textura del jugador

void load_floor_texture(SDL_Renderer* renderer);
void load_ceiling_texture(SDL_Renderer* renderer);
void load_player_texture(SDL_Renderer* renderer);
void free_floor_texture();
void free_ceiling_texture();
void free_player_texture();


