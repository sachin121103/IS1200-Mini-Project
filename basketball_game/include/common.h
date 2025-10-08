#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>

/* Screen dimensions */
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

/* Frame timing */
#define TARGET_FPS 30
#define FRAME_TIME_MS (1000 / TARGET_FPS)
#define FRAME_TIME_SEC (1.0f / TARGET_FPS)

/* Physics constants */
#define GRAVITY 980         /* pixels/s^2 */
#define MAX_SHOT_POWER 50
#define MIN_SHOT_POWER 10
#define BALL_RADIUS 6

/* Game constants */
#define BALL_RETURN_DELAY 2000  /* milliseconds */
#define POINTS_TO_MOVE_HOOP 5
#define MAX_BUTTON_PRESS_TIME 2000  /* milliseconds */

/* Player constants */
#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 40
#define PLAYER_MIN_DEPTH 0
#define PLAYER_MAX_DEPTH 10
#define PLAYER_START_X 80
#define PLAYER_START_Y 200

/* Hoop constants */
#define HOOP_WIDTH 30
#define HOOP_HEIGHT 5
#define HOOP_START_X 160
#define HOOP_START_Y 80

/* Court dimensions */
#define FLOOR_Y (SCREEN_HEIGHT - 20)

/* Colors (RGB565 format) */
#define COLOR_BLACK       0x0000
#define COLOR_WHITE       0xFFFF
#define COLOR_RED         0xF800
#define COLOR_GREEN       0x07E0
#define COLOR_BLUE        0x001F
#define COLOR_YELLOW      0xFFE0
#define COLOR_CYAN        0x07FF
#define COLOR_MAGENTA     0xF81F
#define COLOR_ORANGE      0xFD20  /* Basketball orange */
#define COLOR_COURT_BROWN 0x8A22  /* Court wood color */
#define COLOR_HOOP_RED    0xF800

/* Game structures */
typedef struct {
    int16_t x, y;           /* Position */
    int16_t vx, vy;         /* Velocity (pixels per frame) */
    bool active;            /* Is ball in flight? */
} Ball;

typedef struct {
    int16_t x, y;           /* Screen position */
    uint8_t depth_position; /* 0 (close) to 10 (far) */
} Player;

typedef struct {
    int16_t x, y;           /* Position */
    uint16_t width, height; /* Dimensions */
} Hoop;

typedef struct {
    uint8_t score;
    bool game_active;
    bool ball_in_flight;
    uint32_t ball_return_timer;
    uint32_t shot_start_time;
    bool charging_shot;
} GameState;

/* Game phases */
typedef enum {
    PHASE_READY,
    PHASE_CHARGING,
    PHASE_SHOOTING,
    PHASE_RETURNING,
    PHASE_SCORED
} GamePhase;

#endif /* COMMON_H */