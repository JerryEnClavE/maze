#include <math.h>
#include "../include/player.h"
#include "../include/map.h"
#include "../include/constants.h" // Incluye el archivo de constantes

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

void handle_mouse_movement(int mouse_x, int mouse_y, Player* player, int screen_width, int screen_height) {
    int center_x = screen_width / 2;
    int center_y = screen_height / 2;
    float sensitivity = 0.1f;

    int delta_x = mouse_x - center_x;
    player->angle += delta_x * sensitivity;

    // Opcional: Mover el ratón de vuelta al centro de la pantalla
    // SDL_WarpMouseInWindow(window, center_x, center_y);
