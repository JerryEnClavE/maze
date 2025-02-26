#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define TILE_SIZE 50
#define FOV (M_PI / 3)
#define NUM_RAYS 120
#define MAX_DEPTH 800

SDL_Window* window;
SDL_Renderer* renderer;
double player_x = 150, player_y = 150, player_angle = 0;

int world_map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

void cast_rays() {
    double start_angle = player_angle - (FOV / 2);
    for (int ray = 0; ray < NUM_RAYS; ray++) {
        double angle = start_angle + ((double)ray / NUM_RAYS) * FOV;
        double sin_a = sin(angle), cos_a = cos(angle);
        
        for (int depth = 0; depth < MAX_DEPTH; depth++) {
            int target_x = (int)(player_x + depth * cos_a) / TILE_SIZE;
            int target_y = (int)(player_y + depth * sin_a) / TILE_SIZE;
            
            if (world_map[target_y][target_x] == 1) {
                depth *= cos(player_angle - angle);
                int proj_height = 5000 / (depth + 0.0001);
                int color = 255 - (depth / 3);
                SDL_SetRenderDrawColor(renderer, color, color, color, 255);
                SDL_RenderDrawLine(renderer, ray * (WIDTH / NUM_RAYS), (HEIGHT / 2) - (proj_height / 2), ray * (WIDTH / NUM_RAYS), (HEIGHT / 2) + (proj_height / 2));
                break;
            }
        }
    }
}

void move_player(const Uint8* keys) {
    double speed = 3;
    if (keys[SDL_SCANCODE_W]) {
        player_x += speed * cos(player_angle);
        player_y += speed * sin(player_angle);
    }
    if (keys[SDL_SCANCODE_S]) {
        player_x -= speed * cos(player_angle);
        player_y -= speed * sin(player_angle);
    }
    if (keys[SDL_SCANCODE_A]) player_angle -= 0.05;
    if (keys[SDL_SCANCODE_D]) player_angle += 0.05;
}

void cast_rays();
void move_player(const Uint8* keys);

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        move_player(keys);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        cast_rays();
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

