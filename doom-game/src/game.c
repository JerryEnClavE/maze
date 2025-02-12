/doom-game/doom-game/src/game.c

#include "game.h"
#include <SDL2/SDL_image.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *player_texture = NULL;

/**
 * load_texture - Loads a texture from a file.
 * @file: The path to the image file.
 * @renderer: The SDL renderer.
 *
 * Return: The loaded texture, or NULL on failure.
 */
SDL_Texture* load_texture(const char *file, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *loaded_image = IMG_Load(file);

    if (loaded_image == NULL)
    {
        printf("Failed to load image %s: %s\n", file, IMG_GetError());
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
    SDL_FreeSurface(loaded_image);

    if (texture == NULL)
    {
        printf("Failed to create texture from %s: %s\n", file, SDL_GetError());
    }

    return texture;
}

/**
 * start_game - Initializes the game state.
 *
 * This function sets up the initial conditions for the game,
 * including loading resources and setting the starting player
 * position.
 */
void start_game(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Doom Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    player_texture = load_texture("path/to/player_texture.png", renderer);
    if (player_texture == NULL)
    {
        printf("Failed to load player texture!\n");
        return;
    }

    // Initialize other game state and load resources
}

/**
 * update_game - Updates the game state.
 *
 * This function is called every frame to update the game logic,
 * including player movements, enemy actions, and collision
 * detection.
 */
void update_game(void)
{
    // Update game state and handle logic
}

/**
 * render_game - Renders the game graphics.
 *
 * This function draws the current game state to the screen,
 * including the player, enemies, and environment.
 */
void render_game(void)
{
    SDL_RenderClear(renderer);

    // Render player texture
    SDL_Rect player_rect = { 100, 100, 50, 50 }; // Example position and size
    SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);

    SDL_RenderPresent(renderer);
}

/**
 * handle_input - Processes user input for the game.
 *
 * This function checks for user inputs and updates the game
 * state accordingly, such as moving the player or triggering
 * actions.
 */
void handle_input(void)
{
    // Process user input and update game state
}

/**
 * end_game - Cleans up resources and ends the game.
 *
 * This function is called when the game is over to free
 * resources and perform any necessary cleanup.
 */
void end_game(void)
{
    SDL_DestroyTexture(player_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}