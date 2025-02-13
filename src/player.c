#include "player.h"

Player init_player(float start_x, float start_y) {
    Player player;
    player.x = start_x;
    player.y = start_y;
    player.angle = 0; // Initial angle
    return player;
}

void handle_input(Player *player, int *running) {
    // Handle keyboard input for player movement and quitting
}

void update_player(Player *player, Map *map) {
    // Update player position based on input and collision detection
}