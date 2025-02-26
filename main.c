#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_SIZE 15
#define TILE_SIZE 32
#define FOV 90.0  // Campo de visión ajustado a 90 grados exactos
#define NUM_RAYS (SCREEN_WIDTH/2)  // Más rayos para mejor calidad
#define WALL_HEIGHT 32.0  // Paredes mucho más bajas para más amplitud
#define PLAYER_HEIGHT (WALL_HEIGHT / 2.0)
#define PROJECTION_PLANE ((SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * M_PI / 180.0))
#define MOUSE_SENSITIVITY 0.3f
#define WALL_SLICE_WIDTH 2  // Columnas más delgadas para mejor resolución

// 0 = camino, 1 = pared gris clara, 2 = pared gris oscura
int map[MAP_SIZE][MAP_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct {
    float x;
    float y;
    float angle;
    int mouse_x;        // Posición actual del ratón
    int mouse_y;
    int is_mouse_locked;  // Estado del bloqueo del ratón
} Player;

void draw_3d_view(SDL_Renderer* renderer, Player* player) {
    float ray_angle = player->angle - FOV/2;
    float ray_angle_step = FOV / NUM_RAYS;

    // Dibujar cielo (más alto)
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);  // Azul cielo más realista
    SDL_Rect sky = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 0.65};  // Cielo más grande
    SDL_RenderFillRect(renderer, &sky);

    // Dibujar suelo (más bajo)
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);  // Suelo más claro
    SDL_Rect floor = {0, SCREEN_HEIGHT * 0.65, SCREEN_WIDTH, SCREEN_HEIGHT * 0.35};
    SDL_RenderFillRect(renderer, &floor);

    for (int i = 0; i < NUM_RAYS; i++) {
        float rad = ray_angle * M_PI / 180.0;
        float ray_x = player->x;
        float ray_y = player->y;
        float sin_a = sin(rad);
        float cos_a = cos(rad);
        float distance = 0;
        int hit_wall = 0;
        int wall_type = 0;

        float step_size = 0.02;  // Pasos más pequeños para mejor precisión
        while (!hit_wall && distance < 40) {  // Distancia de visión mucho mayor
            ray_x += cos_a * step_size;
            ray_y += sin_a * step_size;
            distance += step_size;

            int map_x = (int)ray_x;
            int map_y = (int)ray_y;

            if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE) {
                if (map[map_y][map_x] > 0) {
                    hit_wall = 1;
                    wall_type = map[map_y][map_x];
                }
            }
        }

        float ca = player->angle - ray_angle;
        if (ca < 0) ca += 360;
        if (ca >= 360) ca -= 360;
        distance = distance * cos(ca * M_PI / 180.0);

        float wall_height = (WALL_HEIGHT * PROJECTION_PLANE) / (distance + 0.0001);
        
        int wall_top = (SCREEN_HEIGHT - wall_height) / 2;
        int wall_bottom = (SCREEN_HEIGHT + wall_height) / 2;
        
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= SCREEN_HEIGHT) wall_bottom = SCREEN_HEIGHT - 1;

        // Color base según el tipo de pared
        int base_color;
        if (wall_type == 1) {
            base_color = 180;  // Paredes más claras
        } else {
            base_color = 140;  // Paredes tipo 2 también más claras
        }

        // Sombreado basado en la distancia (mucho menos intenso)
        int shade = base_color - (int)(distance * 2);  // Sombreado más suave
        if (shade < 60) shade = 60;  // Mínimo más alto para mejor visibilidad
        if (shade > base_color) shade = base_color;

        // Dibujar columna más delgada
        SDL_Rect wall_slice = {
            i * WALL_SLICE_WIDTH,
            wall_top,
            WALL_SLICE_WIDTH,
            wall_bottom - wall_top
        };
        SDL_SetRenderDrawColor(renderer, shade, shade, shade + 15, 255);  // Más contraste
        SDL_RenderFillRect(renderer, &wall_slice);

        ray_angle += ray_angle_step;
    }
}

void draw_minimap(SDL_Renderer* renderer, Player* player) {
    int minimap_size = 150;
    float scale = (float)minimap_size / (MAP_SIZE * TILE_SIZE);
    
    // Dibujar fondo del minimapa
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 192);
    SDL_Rect minimap_bg = {0, 0, minimap_size, minimap_size};
    SDL_RenderFillRect(renderer, &minimap_bg);

    // Dibujar paredes en el minimapa
    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            SDL_Rect tile = {
                x * TILE_SIZE * scale,
                y * TILE_SIZE * scale,
                TILE_SIZE * scale - 1,
                TILE_SIZE * scale - 1
            };

            if (map[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 180, 180, 180, 128);  // Pared gris clara
            } else if (map[y][x] == 2) {
                SDL_SetRenderDrawColor(renderer, 120, 120, 120, 128);  // Pared gris oscura
            } else {
                SDL_SetRenderDrawColor(renderer, 40, 40, 40, 128);     // Camino
            }
            SDL_RenderFillRect(renderer, &tile);
        }
    }

    // Dibujar jugador en el minimapa
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect player_dot = {
        player->x * TILE_SIZE * scale - 2,
        player->y * TILE_SIZE * scale - 2,
        4,
        4
    };
    SDL_RenderFillRect(renderer, &player_dot);

    // Dibujar dirección del jugador
    float dir_x = player->x * TILE_SIZE * scale + cos(player->angle * M_PI / 180.0) * 10;
    float dir_y = player->y * TILE_SIZE * scale + sin(player->angle * M_PI / 180.0) * 10;
    SDL_RenderDrawLine(renderer,
        player->x * TILE_SIZE * scale,
        player->y * TILE_SIZE * scale,
        dir_x,
        dir_y
    );
}

void handle_mouse(Player* player, SDL_Window* window) {
    if (!player->is_mouse_locked) {
        return;
    }

    int new_mouse_x, new_mouse_y;
    SDL_GetMouseState(&new_mouse_x, &new_mouse_y);

    // Calcular el cambio en la posición del ratón
    int dx = new_mouse_x - player->mouse_x;
    
    // Actualizar el ángulo basado en el movimiento horizontal del ratón
    player->angle += dx * MOUSE_SENSITIVITY;
    
    // Mantener el ángulo entre 0 y 360 grados
    if (player->angle < 0) player->angle += 360;
    if (player->angle >= 360) player->angle -= 360;

    // Centrar el ratón en la ventana
    SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    player->mouse_x = SCREEN_WIDTH/2;
    player->mouse_y = SCREEN_HEIGHT/2;
}

void handle_input(const Uint8* keys, Player* player) {
    float move_speed = 0.25f;  // Velocidad de movimiento aumentada
    float strafe_speed = 0.2f;  // Velocidad lateral aumentada

    float dx = 0, dy = 0;

    // Movimiento adelante/atrás con W/S o el botón derecho/izquierdo del ratón
    if (keys[SDL_SCANCODE_W] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
        dx += cos(player->angle * M_PI / 180.0) * move_speed;
        dy += sin(player->angle * M_PI / 180.0) * move_speed;
    }
    if (keys[SDL_SCANCODE_S] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
        dx -= cos(player->angle * M_PI / 180.0) * move_speed;
        dy -= sin(player->angle * M_PI / 180.0) * move_speed;
    }

    // Movimiento lateral con A/D o el botón central del ratón
    if (keys[SDL_SCANCODE_A]) {
        dx += cos((player->angle - 90) * M_PI / 180.0) * strafe_speed;
        dy += sin((player->angle - 90) * M_PI / 180.0) * strafe_speed;
    }
    if (keys[SDL_SCANCODE_D]) {
        dx += cos((player->angle + 90) * M_PI / 180.0) * strafe_speed;
        dy += sin((player->angle + 90) * M_PI / 180.0) * strafe_speed;
    }

    // Verificar colisiones y aplicar movimiento
    float new_x = player->x + dx;
    float new_y = player->y + dy;

    // Verificar colisiones con margen
    float margin = 0.2f;
    if (map[(int)player->y][(int)(new_x + (dx > 0 ? margin : -margin))] == 0) {
        player->x = new_x;
    }
    if (map[(int)(new_y + (dy > 0 ? margin : -margin))][(int)player->x] == 0) {
        player->y = new_y;
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no pudo inicializarse! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Raycasting 3D", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN);

    if (!window) {
        printf("La ventana no pudo crearse! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer no pudo crearse! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inicializar jugador con el ratón
    Player player = {
        .x = 5.0f,
        .y = 5.0f,
        .angle = 0.0f,
        .mouse_x = SCREEN_WIDTH/2,
        .mouse_y = SCREEN_HEIGHT/2,
        .is_mouse_locked = 1  // Iniciar con el ratón bloqueado
    };

    // Centrar el ratón inicialmente
    SDL_WarpMouseInWindow(window, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_ShowCursor(SDL_DISABLE);

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    // Alternar el bloqueo del ratón con ESC
                    player.is_mouse_locked = !player.is_mouse_locked;
                    SDL_ShowCursor(!player.is_mouse_locked);
                }
            }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        handle_input(keys, &player);
        handle_mouse(&player, window);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_3d_view(renderer, &player);
        draw_minimap(renderer, &player);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_ShowCursor(SDL_ENABLE);  // Restaurar el cursor antes de salir
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


