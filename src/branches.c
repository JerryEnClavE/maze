#include "../inc/branches.h"
#include <SDL2/SDL.h>

void init_branches(Branch *branches, int num_branches) {
    // Initialize branches with some values
    for (int i = 0; i < num_branches; i++) {
        branches[i].x = i * 10.0f;
        branches[i].y = i * 5.0f;
    }
}

void update_branches(Branch *branches, int num_branches) {
    // Update branches positions or states
    for (int i = 0; i < num_branches; i++) {
        branches[i].x += 1.0f;
        branches[i].y += 1.0f;
    }
}

void render_branches(SDL_Renderer *renderer, Branch *branches, int num_branches) {
    // Render branches on the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < num_branches; i++) {
        SDL_RenderDrawPoint(renderer, (int)branches[i].x, (int)branches[i].y);
    }
}