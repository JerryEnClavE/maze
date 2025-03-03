#include <SDL2/SDL.h>
#include <math.h> // Include math.h for M_PI

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "../inc/input.h"
#include "../inc/camera.h"


/**
 * handle_input - Handles user input for camera movement and rotation.
 * @event: Pointer to the SDL_Event structure containing event data.
 * @camera: Pointer to the camera structure to update its position and angle.
 */
void handle_input(SDL_Event *event, camera *camera)
{
    // Process all events in the queue
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            // Handle quit event (exit the application)
            exit(0);
        }
        if (event->type == SDL_KEYDOWN)
        {
            // Handling camera movement and rotation based on key press
            switch (event->key.keysym.sym)
            {
                case SDLK_LEFT:
                    camera->angle -= 5; // Rotate left (counterclockwise)
                    break;
                case SDLK_RIGHT:
                    camera->angle += 5; // Rotate right (clockwise)
                    break;
                case SDLK_w:
                    camera->pos.x += cos(camera->angle * M_PI / 180) * camera->speed; // Move forward
                    camera->pos.y += sin(camera->angle * M_PI / 180) * camera->speed;
                    break;
                case SDLK_s:
                    camera->pos.x -= cos(camera->angle * M_PI / 180) * camera->speed; // Move backward
                    camera->pos.y -= sin(camera->angle * M_PI / 180) * camera->speed;
                    break;
                case SDLK_a:
                    camera->pos.x -= cos((camera->angle + 90) * M_PI / 180) * camera->speed; // Move left (strafe)
                    camera->pos.y -= sin((camera->angle + 90) * M_PI / 180) * camera->speed;
                    break;
                case SDLK_d:
                    camera->pos.x += cos((camera->angle + 90) * M_PI / 180) * camera->speed; // Move right (strafe)
                    camera->pos.y += sin((camera->angle + 90) * M_PI / 180) * camera->speed;
                    break;
            }
        }
    }
}
