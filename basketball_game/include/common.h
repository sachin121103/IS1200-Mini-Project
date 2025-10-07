#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

// Screen dimensions
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Game constants
#define GRAVITY 980  // pixels/s^2 (adjust as needed)
#define MAX_SHOT_POWER 50
#define BALL_RETURN_DELAY 2000  // milliseconds

// Structures
typedef struct {
    int16_t x, y;
    int16_t vx, vy;  // velocity
    uint8_t active;
} Ball;

typedef struct {
    int16_t x, y;
    uint8_t position;  // 0-10 for front to back
} Player;

typedef struct {
    int16_t x, y;
    uint16_t width, height;
} Hoop;

typedef struct {
    uint8_t score;
    uint8_t game_active;
    uint32_t ball_return_timer;
} GameState;

#endif