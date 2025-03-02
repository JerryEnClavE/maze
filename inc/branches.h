#ifndef BRANCHES_H
#define BRANCHES_H

#include <SDL2/SDL.h> // Incluir SDL para SDL_Renderer
#include "branch.h"  // Incluir el archivo de encabezado que define Branch

void render_branches(SDL_Renderer *renderer, Branch *branches, int num_branches);

#endif // BRANCHES_H