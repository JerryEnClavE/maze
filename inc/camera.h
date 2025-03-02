#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float x;
    float y;
} Position;

typedef struct {
    Position pos;
    float angle;
    float speed;
} camera;

#endif // CAMERA_H