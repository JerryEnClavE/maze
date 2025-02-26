#include <SDL2/SDL.h>
#include "include/player.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOUSE_SENSITIVITY 0.1f

void handle_mouse(Player* player, SDL_Window* window) {
    if (!player->is_mouse_locked) {
        return;
    }

    int new_mouse_x, new_mouse_y;
    SDL_GetMouseState(&new_mouse_x, &new_mouse_y);

    int dx = new_mouse_x - player->mouse_x;
    
    player->angle += dx * MOUSE_SENSITIVITY;
    
    if (player->angle < 0) player->angle += 360;
    if (player->angle >= 360) player->angle -= 360;

    SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    player->mouse_x = SCREEN_WIDTH/2;
    player->mouse_y = SCREEN_HEIGHT/2;
}

void handle_input(const Uint8* keys, Player* player) {
    float move_speed = 0.25f;
    float strafe_speed = 0.2f;

    float dx = 0, dy = 0;

    if (keys[SDL_SCANCODE_W] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
        dx += cos(player->angle * M_PI / 180.0) * move_speed;
        dy += sin(player->angle * M_PI / 180.0) * move_speed;
    }
    if (keys[SDL_SCANCODE_S] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
        dx -= cos(player->angle * M_PI / 180.0) * move_speed;
        dy -= sin(player->angle * M_PI / 180.0) * move_speed;
    }

    if (keys[SDL_SCANCODE_A]) {
        dx += cos((player->angle - 90) * M_PI / 180.0) * strafe_speed;
        dy += sin((player->angle - 90) * M_PI / 180.0) * strafe_speed;
    }
    if (keys[SDL_SCANCODE_D]) {
        dx += cos((player->angle + 90) * M_PI / 180.0) * strafe_speed;
        dy += sin((player->angle + 90) * M_PI / 180.0) * strafe_speed;
    }
    extern int map[100][100]; // Adjust the size as per your map dimensions

    float margin = 0.2f;
    float new_x = player->x + dx;
    float new_y = player->y + dy;

    float margin = 0.2f;
    if (map[(int)player->y][(int)(new_x + (dx > 0 ? margin : -margin))] == 0) {
        player->x = new_x;
    }
    if (map[(int)(new_y + (dy > 0 ? margin : -margin))][(int)player->x] == 0) {
        player->y = new_y;
    }
}

void init_player(Player* player) {
    player->x = 5.0f;
    player->y = 5.0f;
    player->angle = 0.0f;
    player->mouse_x = SCREEN_WIDTH / 2;
    player->mouse_y = SCREEN_HEIGHT / 2;
    player->is_mouse_locked = 1;
}