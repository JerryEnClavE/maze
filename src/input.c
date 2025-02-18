#include "../headers/header.h"

/**
 * processKeyDown - Handle key down events
 * @event: SDL event containing key information
 */
void processKeyDown(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            GameRunning = false;
            break;
        case SDLK_UP:
        case SDLK_w:
            player.walkDirection = +1;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            player.walkDirection = -1;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            player.turnDirection = +1;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            player.turnDirection = -1;
            break;
        default:
            break;
    }
}

/**
 * processKeyUp - Handle key up events
 * @event: SDL event containing key information
 */
void processKeyUp(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_w:
        case SDLK_DOWN:
        case SDLK_s:
            player.walkDirection = 0;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
        case SDLK_LEFT:
        case SDLK_a:
            player.turnDirection = 0;
            break;
        default:
            break;
    }
}

/**
 * handleInput - Process all input events
 */
void handleInput(void) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                GameRunning = false;
                break;
            case SDL_KEYDOWN:
                processKeyDown(event);
                break;
            case SDL_KEYUP:
                processKeyUp(event);
                break;
            default:
                break;
        }
    }
}