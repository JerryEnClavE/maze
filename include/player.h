#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    float x, y;
    float angle;
    int mouse_x;
    int mouse_y;
    int is_mouse_locked;
} Player;

void handle_mouse(Player* player, SDL_Window* window);
void handle_input(const Uint8* keys, Player* player);
void init_player(Player* player);

#endif // PLAYER_H