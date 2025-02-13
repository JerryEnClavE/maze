#include <SDL2/SDL.h>
#include "raycasting.h"
#include "map_parser.h"
#include "player.h"
#include "rendering.h"
#include "textures.h"
#include "enemies.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Load map
    Map map = load_map("maze.txt");

    // Initialize player
    Player player = init_player(map.start_x, map.start_y);

    // Main game loop
    int running = 1;
    while (running) {
        handle_input(&player, &running);
        update_player(&player, &map);
        render(&player, &map);
    }

    // Clean up
    SDL_Quit();
    return 0;
}
