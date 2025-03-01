// input.h
#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

// Function to handle keyboard input
void handle_keyboard_input(SDL_Event *event);

// Function to handle mouse input
void handle_mouse_input(SDL_Event *event);

// Function to initialize input handling
void init_input(void);

// Function to clean up input resources
void cleanup_input(void);

#endif // INPUT_H