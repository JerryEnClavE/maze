#ifndef UTILS_H
#define UTILS_H

/**
 * load_resources - Loads game resources such as textures and sounds.
 *
 * Return: 0 on success, or -1 on failure.
 */
int load_resources(void);

/**
 * handle_collisions - Checks for collisions between game objects.
 *
 * Return: 1 if a collision is detected, 0 otherwise.
 */
int handle_collisions(void);

/**
 * manage_settings - Loads and saves game settings.
 *
 * Return: 0 on success, or -1 on failure.
 */
int manage_settings(void);

/**
 * cleanup_resources - Frees allocated resources before exiting the game.
 */
void cleanup_resources(void);

/**
 * initialize_game - Initializes game variables and settings.
 *
 * Return: 0 on success, or -1 on failure.
 */
int initialize_game(void);

#endif /* UTILS_H */