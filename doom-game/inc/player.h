#ifndef PLAYER_H
#define PLAYER_H

/**
 * struct player - Represents a player in the game.
 * @name: The name of the player.
 * @health: The current health of the player.
 * @position_x: The player's current x position.
 * @position_y: The player's current y position.
 */
struct player
{
    char *name;
    int health;
    float position_x;
    float position_y;
};

/**
 * init_player - Initializes a player with default values.
 * @p: Pointer to the player structure to initialize.
 * @name: The name of the player.
 */
void init_player(struct player *p, char *name);

/**
 * move_player - Moves the player in the specified direction.
 * @p: Pointer to the player structure.
 * @delta_x: Change in x position.
 * @delta_y: Change in y position.
 */
void move_player(struct player *p, float delta_x, float delta_y);

/**
 * take_damage - Reduces the player's health by a specified amount.
 * @p: Pointer to the player structure.
 * @damage: The amount of damage to apply.
 */
void take_damage(struct player *p, int damage);

/**
 * is_alive - Checks if the player is still alive.
 * @p: Pointer to the player structure.
 * 
 * Return: 1 if the player is alive, 0 otherwise.
 */
int is_alive(struct player *p);

#endif /* PLAYER_H */