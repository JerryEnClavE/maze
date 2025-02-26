#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600
#define TILE_SIZE 64
#define FOV (M_PI / 2) // Ajusta el campo de visión a 90 grados
#define NUM_RAYS 120
#define MAX_DEPTH 800
#define MINIMAP_SCALE 0.2

SDL_Window* window;
SDL_Renderer* renderer;
double player_x = WIDTH / 2;
double player_y = HEIGHT / 2;
double player_angle = 0;

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
    double move_speed = 10; // Ajusta la velocidad de movimiento
    double rot_speed = 0.2; // Ajusta la sensibilidad de rotación

    double new_x = player_x;
    double new_y = player_y;

    if (keys[SDL_SCANCODE_W]) {
        new_x += move_speed * cos(player_angle);
        new_y += move_speed * sin(player_angle);
    }
    if (keys[SDL_SCANCODE_S]) {
        new_x -= move_speed * cos(player_angle);
        new_y -= move_speed * sin(player_angle);
    }
    if (keys[SDL_SCANCODE_A]) player_angle -= rot_speed;
    if (keys[SDL_SCANCODE_D]) player_angle += rot_speed;

    // Verificación de colisión
    int map_x = (int)(new_x / TILE_SIZE);
    int map_y = (int)(new_y / TILE_SIZE);
    if (world_map[map_y][map_x] == 0) {
        // Interpolación lineal para un movimiento más suave
        player_x = player_x + (new_x - player_x) * 0.1;
        player_y = player_y + (new_y - player_y) * 0.1;
    }
}

void draw_minimap(SDL_Renderer* renderer) {
    int minimap_tile_size = TILE_SIZE * MINIMAP_SCALE;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (world_map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_Rect tile_rect = {x * minimap_tile_size, y * minimap_tile_size, minimap_tile_size, minimap_tile_size};
            SDL_RenderFillRect(renderer, &tile_rect);
        }
    }

    // Dibujar al jugador en el minimapa
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect player_rect = {
        (int)(player_x * MINIMAP_SCALE) - 2,
        (int)(player_y * MINIMAP_SCALE) - 2,
        4, 4
    };
    SDL_RenderFillRect(renderer, &player_rect);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    bool running = true;
    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        move_player(keys);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        cast_rays();
        draw_minimap(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

