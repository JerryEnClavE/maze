#include <SDL2/SDL.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800
#define MAP_SIZE 100
#define CELL_SIZE (WIDTH / MAP_SIZE)

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Mapa 2D con Jugador", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Limpiar la pantalla con color blanco
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    // Coordenadas del jugador
    int player_x = 50;
    int player_y = 50;

    // Dibujar el jugador como un punto rojo
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect player = { player_x * CELL_SIZE, player_y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
    SDL_RenderFillRect(ren, &player);

    // Mostrar el mapa
    SDL_RenderPresent(ren);

    // Esperar 5 segundos antes de salir
    SDL_Delay(5000);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}