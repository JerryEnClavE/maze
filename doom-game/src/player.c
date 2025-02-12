/Proyect-Maze/doom-game/src/player.c

#include "player.h"

/**
 * move_player - Moves the player in the specified direction.
 * @player: Pointer to the player structure.
 * @direction: Direction to move the player (e.g., 'W', 'A', 'S', 'D').
 */
void move_player(Player *player, char direction)
{
    if (direction == 'W')
    {
        player->y -= player->speed;
    }
    else if (direction == 'S')
    {
        player->y += player->speed;
    }
    else if (direction == 'A')
    {Para añadir texturas a tu juego, necesitarás cargar las imágenes de las texturas y luego renderizarlas en la pantalla. Aquí tienes un ejemplo de cómo podrías hacerlo utilizando la biblioteca SDL2 para manejar gráficos y texturas.

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
        player->x -= player->speed;
    }
    else if (direction == 'D')
    {
        player->x += player->speed;
    }
}

/**
 * take_damage - Reduces the player's health by a specified amount.
 * @player: Pointer to the player structure.
 * @damage: Amount of damage to apply to the player.
 */
void take_damage(Player *player, int damage)
{
    player->health -= damage;
    if (player->health < 0)
    {
        player->health = 0;
    }
}

/**
 * heal_player - Increases the player's health by a specified amount.
 * @player: Pointer to the player structure.
 * @heal: Amount of health to restore to the player.
 */
void heal_player(Player *player, int heal)
{
    player->health += heal;
    if (player->health > player->max_health)
    {
        player->health = player->max_health;
    }
}

/**
 * interact_with_environment - Handles player interactions with the environment.
 * @player: Pointer to the player structure.
 * @environment: Pointer to the environment structure.
 */
void interact_with_environment(Player *player, Environment *environment)
{
    // Interaction logic goes here
}

/**
 * reset_player - Resets the player's attributes to default values.
 * @player: Pointer to the player structure.
 */
void reset_player(Player *player)
{
    player->health = player->max_health;
    player->x = 0;
    player->y = 0;
}