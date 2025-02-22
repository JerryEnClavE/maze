#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    float x, y;
    float angle;
} Player;

void handle_input(const Uint8* keys, Player* player);

#endif // PLAYER_H