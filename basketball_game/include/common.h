#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>

// Screen dimensions
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Physics constants (Person A can tune later)
#define GRAVITY 980
#define MAX_SHOT_POWER 50
#define MIN_SHOT_POWER 10
#define BALL_RADIUS 6

// Game constants
#define BALL_RETURN_DELAY 2000  // milliseconds
#define POINTS_TO_MOVE_HOOP 5

// Player constants
#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 40
#define PLAYER_MAX_DEPTH 10

// Hoop constants
#define HOOP_WIDTH 30
#define HOOP_HEIGHT 5

// Colors (RGB565 format)
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_ORANGE  0xFD20
#define COLOR_RED     0xF800
#define COLOR_BLUE    0x001F

// Shared structures
typedef struct {
    int16_t x, y;
    int16_t vx, vy;
    bool active;
} Ball;

typedef struct {
    int16_t x, y;
    uint8_t depth_position;  // 0-10
} Player;

typedef struct {
    int16_t x, y;
    uint16_t width, height;
} Hoop;

typedef struct {
    uint8_t score;
    bool game_active;
    uint32_t ball_return_timer;
} GameState;

#endif