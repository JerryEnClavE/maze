#include <SDL2/SDL.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "map.h"
#include "player.h"

void handle_input(const Uint8* keys, Player* player) {
    float move_speed = 5.0;
    float rotate_speed = 3.0;
    float new_x = player->x;
    float new_y = player->y;

    if (keys[SDL_SCANCODE_W]) {
        new_x += cos(player->angle * M_PI / 180) * move_speed;
        new_y += sin(player->angle * M_PI / 180) * move_speed;
    }
    if (keys[SDL_SCANCODE_S]) {
        new_x -= cos(player->angle * M_PI / 180) * move_speed;
        new_y -= sin(player->angle * M_PI / 180) * move_speed;
    }
    if (map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0) {
        player->x = new_x;
        player->y = new_y;
    }

    if (keys[SDL_SCANCODE_A]) player->angle -= rotate_speed;
    if (keys[SDL_SCANCODE_D]) player->angle += rotate_speed;
}