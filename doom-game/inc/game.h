#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

/**
 * struct game_state - Represents the current state of the game.
 * @is_running: Indicates if the game is currently running.
 * @score: The current score of the player.
 * @level: The current level of the game.
 */
typedef struct game_state
{
    int is_running;
    int score;
    int level;
} game_state_t;

/**
 * start_game - Initializes the game state and resources.
 * 
 * Return: 0 on success, or a negative error code on failure.
 */
void start_game(void);

/**
 * update_game - Updates the game state based on player input and time.
 * 
 * Return: 0 on success, or a negative error code on failure.
 */
void update_game(void);

/**
 * render_game - Renders the current game state to the screen.
 * 
 * Return: 0 on success, or a negative error code on failure.
 */
void render_game(void);

/**
 * handle_input - Handles player input.
 */
void handle_input(void);

/**
 * end_game - Cleans up resources and ends the game.
 * 
 * Return: 0 on success, or a negative error code on failure.
 */
void end_game(void);

/**
 * load_texture - Loads a texture from a file.
 * @file: The path to the texture file.
 * @renderer: The SDL renderer.
 * 
 * Return: A pointer to the loaded texture, or NULL on failure.
 */
SDL_Texture* load_texture(const char *file, SDL_Renderer *renderer);

#endif /* GAME_H */