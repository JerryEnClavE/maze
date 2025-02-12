/Proyect-Maze/doom-game/src/utils.cPara añadir texturas a tu juego, necesitarás cargar las imágenes de las texturas y luego renderizarlas en la pantalla. Aquí tienes un ejemplo de cómo podrías hacerlo utilizando la biblioteca SDL2 para manejar gráficos y texturas.

Primero, asegúrate de tener SDL2 instalada en tu sistema. Puedes instalarla usando el siguiente comando:

```bash
sudo apt-get install libsdl2-dev
```

Luego, actualiza tu archivo `game.h` para incluir las funciones necesarias para cargar y renderizar texturas:

```c
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

// Function prototypes
void start_game(void);
void update_game(void);
void render_game(void);
void handle_input(void);
void end_game(void);
SDL_Texture* load_texture(const char *file, SDL_Renderer *renderer);

#endif /* GAME_H */
```

A continuación, actualiza tu archivo game.c para implementar la carga y renderización de texturas:

```c
#include "game.h"
#include "utils.h"
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

    player_texture = load_texture("assets/player_texture.png", renderer);
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
```

Este código inicializa SDL2, carga una textura para el jugador desde un archivo PNG y la renderiza en la pantalla. Asegúrate de reemplazar `"path/to/player_texture.png"` con la ruta real de tu archivo de textura.

Finalmente, actualiza tu `Makefile` para compilar el proyecto con SDL2:

```makefile
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=gnu89 -pedantic
LDFLAGS = -lSDL2 -lSDL2_image

SRC = src/main.c src/game.c src/player.c src/utils.c
OBJ = $(SRC:.c=.o)
EXEC = doom_game

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)

.PHONY: all clean
```

Con estos cambios, deb

#include "utils.h"

/**
 * load_resource - Loads a resource from the specified path.
 * @path: The path to the resource file.
 *
 * Return: Pointer to the loaded resource, or NULL on failure.
 */
void *load_resource(const char *path)
{
    // Implementation for loading a resource
}

/**
 * handle_collision - Checks for collision between two game objects.
 * @obj1: Pointer to the first game object.
 * @obj2: Pointer to the second game object.
 *
 * Return: 1 if a collision occurs, 0 otherwise.
 */
int handle_collision(GameObject *obj1, GameObject *obj2)
{
    // Implementation for handling collision
}

/**
 * manage_settings - Loads or saves game settings.
 * @settings: Pointer to the settings structure.
 * @load: Flag indicating whether to load or save settings.
 *
 * Return: 0 on success, -1 on failure.
 */
int manage_settings(Settings *settings, int load)
{
    // Implementation for managing settings
}

/**
 * free_resource - Frees the memory allocated for a resource.
 * @resource: Pointer to the resource to be freed.
 */
void free_resource(void *resource)
{
    // Implementation for freeing a resource
}

/**
 * print_error - Prints an error message to stderr.
 * @message: The error message to print.
 */
void print_error(const char *message)
{
    // Implementation for printing an error
}