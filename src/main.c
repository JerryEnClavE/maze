#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../inc/map.h"
#include "../inc/player.h"
#include "../inc/textures.h"
#include "../inc/minimap.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FOV 60.0
#define NUM_RAYS SCREEN_WIDTH
#define TILE_SIZE 64
#define texWidth 64
#define texHeight 64

SDL_Texture* wall_texture = NULL;

void render_floor(SDL_Renderer* renderer) {
    SDL_Rect floor_rect = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255); // Color verde oscuro
    SDL_RenderFillRect(renderer, &floor_rect);
}

void cast_rays(SDL_Renderer* renderer, Player* player) {
    if (!renderer || !player) {
        printf("Renderer or player is NULL\n");
        return;
    }

    // Render ceiling (sky)
    SDL_Rect ceiling_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderFillRect(renderer, &ceiling_rect);

    float ray_angle = player->angle - (FOV / 2);
    for (int i = 0; i < NUM_RAYS; i++) {
        // Normalize angle
        while (ray_angle >= 360.0f) ray_angle -= 360.0f;
        while (ray_angle < 0.0f) ray_angle += 360.0f;

        float ray_x = player->x;
        float ray_y = player->y;
        float ray_dx = cos(ray_angle * M_PI / 180);
        float ray_dy = sin(ray_angle * M_PI / 180);
        
        // Variables for DDA algorithm
        int mapX = (int)(ray_x / TILE_SIZE);
        int mapY = (int)(ray_y / TILE_SIZE);
        
        // Length of ray from current position to next x or y-side
        float sideDistX, sideDistY;
        
        // Length of ray from one x or y-side to next x or y-side
        float deltaDistX = (ray_dx == 0) ? 1e30 : fabs(1 / ray_dx);
        float deltaDistY = (ray_dy == 0) ? 1e30 : fabs(1 / ray_dy);
        
        // What direction to step in x or y direction (either +1 or -1)
        int stepX, stepY;
        
        // Calculate step and initial sideDist
        if (ray_dx < 0) {
            stepX = -1;
            sideDistX = (ray_x / TILE_SIZE - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - ray_x / TILE_SIZE) * deltaDistX;
        }
        
        if (ray_dy < 0) {
            stepY = -1;
            sideDistY = (ray_y / TILE_SIZE - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - ray_y / TILE_SIZE) * deltaDistY;
        }
        
        // Perform DDA
        int hit = 0;
        int side = 0; // 0 for NS wall, 1 for EW wall
        
        while (!hit) {
            // Jump to next map square
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            
            // Check if ray has hit a wall
            if (mapY >= 0 && mapX >= 0 && mapY < MAP_HEIGHT && mapX < MAP_WIDTH) {
                if (map[mapY][mapX] == 1) hit = 1;
            } else {
                break; // Ray is out of bounds
            }
        }
        
        if (!hit) {
            ray_angle += FOV / NUM_RAYS;
            continue; // Skip if no wall was hit
        }
        
        // Calculate distance projected on camera direction
        float perpWallDist;
        if (side == 0) {
            perpWallDist = (mapX - ray_x / TILE_SIZE + (1 - stepX) / 2) / ray_dx;
        } else {
            perpWallDist = (mapY - ray_y / TILE_SIZE + (1 - stepY) / 2) / ray_dy;
        }
        perpWallDist *= TILE_SIZE;
        
        // Calculate height of line to draw on screen
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist * TILE_SIZE);
        
        // Calculate where exactly the wall was hit
        float wallX;
        if (side == 0) {
            wallX = ray_y + perpWallDist * ray_dy / TILE_SIZE;
        } else {
            wallX = ray_x + perpWallDist * ray_dx / TILE_SIZE;
        }
        wallX -= floor(wallX);
        
        // X coordinate on the texture
        int texX = (int)(wallX * texWidth);
        if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0)) {
            texX = texWidth - texX - 1;
        }
        
        // Draw the textured vertical line
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
        
        SDL_Rect src_rect = { texX, 0, 1, texHeight };
        SDL_Rect dst_rect = { i, drawStart, 1, drawEnd - drawStart };
        
        if (wall_texture) {
            SDL_RenderCopy(renderer, wall_texture, &src_rect, &dst_rect);
        } else {
            printf("Wall texture is NULL\n");
        }
        
        ray_angle += FOV / NUM_RAYS;
    }
}

void handle_mouse_motion(SDL_MouseMotionEvent* motion, Player* player) {
    float sensitivity = 0.1f;
    player->angle += motion->xrel * sensitivity;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Raycasting with Textures", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    wall_texture = load_texture(renderer, "textures/wall.png");
    if (!wall_texture) {
        printf("Failed to load wall texture\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Player player = {200, 200, 90};
    int running = 1;
    SDL_Event event;
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEMOTION) {
                handle_mouse_motion(&event.motion, &player);
            }
        }
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        handle_input(keys, &player);

        SDL_RenderClear(renderer);
        render_floor(renderer);
        cast_rays(renderer, &player);
        draw_minimap(renderer, &player);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(wall_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
