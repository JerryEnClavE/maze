#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    float x, y;
    float angle;
} Player;

void handle_input(const Uint8* keys, Player* player);
void handle_mouse_movement(int mouse_x, int mouse_y, Player* player);

#endif // PLAYER_H