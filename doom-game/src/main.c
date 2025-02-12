#include <stdio.h>
#include "game.h"
#include "player.h"
#include "utils.h"

/**
 * main - Entry point of the Doom game.
 *
 * This function initializes the game, sets up the main loop,
 * and handles user input and rendering.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int game_running;

    game_running = initialize_game();

    while (game_running)
    {
        handle_input();
        update_game_state();
        render_graphics();
        game_running = check_game_status();
    }

    cleanup_game();
    return (0);
}