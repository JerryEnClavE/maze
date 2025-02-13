#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Define the maximum dimensions for the map
#define MAX_MAP_WIDTH 100
#define MAX_MAP_HEIGHT 100

// Structure to represent the map
typedef struct {
    int width;
    int height;
    int grid[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]; // 0 for empty space, 1 for wall
    float start_x; // Player starting x position
    float start_y; // Player starting y position
} Map;

// Structure to represent the player
typedef struct {
    float x;      // Player x position
    float y;      // Player y position
    float angle;  // Player direction angle
} Player;

// Function prototypes
Map load_map(const char *filename);
Player init_player(float start_x, float start_y);
void handle_input(Player *player, bool *running);
void update_player(Player *player, Map *map);
void render(Player *player, Map *map);
void cast_rays(Player *player, Map *map);
void load_textures();
void draw_texture(SDL_Texture *texture, int x, int y);
void update_enemies(Map *map);
void render_enemies(Map *map);
float distance(float x1, float y1, float x2, float y2);

#endif // MAZE_H