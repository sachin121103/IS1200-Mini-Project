#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>

/* ===========================
   SCREEN CONFIGURATION
   =========================== */
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#define FRAME_TIME_MS 33  // ~30 FPS (33.33ms per frame)

/* ===========================
   PHYSICS CONSTANTS (TUNED)
   =========================== */
#define GRAVITY 100            // Pixels per second squared (tuned for gameplay)
#define MAX_SHOT_POWER 150     // Maximum shot velocity
#define MIN_SHOT_POWER 30      // Minimum shot velocity
#define BALL_RADIUS 6          // Ball size in pixels

/* ===========================
   GAME TIMING
   =========================== */
#define BALL_RETURN_DELAY 2000      // 2 seconds before ball returns
#define POINTS_TO_MOVE_HOOP 5       // Hoop moves every 5 points
#define MAX_BUTTON_PRESS_TIME 2000  // Maximum button hold time (ms)

/* ===========================
   GAME OBJECT DIMENSIONS
   =========================== */
#define HOOP_WIDTH 30
#define HOOP_HEIGHT 5
#define PLAYER_WIDTH 20
#define PLAYER_HEIGHT 40

/* ===========================
   RGB565 COLORS
   =========================== */
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_ORANGE  0xFD20  // Basketball orange
#define COLOR_RED     0xF800
#define COLOR_BLUE    0x001F
#define COLOR_GREEN   0x07E0
#define COLOR_YELLOW  0xFFE0
#define COLOR_COURT_BROWN 0x8A22

/* ===========================
   HARDWARE ADDRESSES
   =========================== */
#define VGA_BASE 0x08000000     // VGA pixel buffer base address
#define KEY_BASE 0xFF200050     // Push button base (verify in Qsys)
#define SWITCH_BASE 0xFF200040  // Switch base (verify in Qsys)

/* ===========================
   GAME STRUCTURES
   =========================== */

// Ball structure with sub-pixel precision
typedef struct {
    int16_t x, y;      // Integer position (pixels)
    int16_t vx, vy;    // Velocity (pixels/second)
    float fx, fy;      // Fractional position accumulators
    bool active;       // Is ball in flight?
} Ball;

// Player structure
typedef struct {
    int16_t x, y;              // Position on screen
    uint8_t depth_position;    // 0 (close) to 10 (far from hoop)
} Player;

// Hoop structure
typedef struct {
    int16_t x, y;              // Position on screen
    uint16_t width, height;    // Dimensions
} Hoop;

// Game state structure
typedef struct {
    uint16_t score;            // Current score
    bool is_charging;          // Is player holding button?
    uint32_t charge_start_time; // When button was pressed
    uint32_t ball_land_time;   // When ball hit the ground
    enum {
        STATE_READY,           // Ready to shoot
        STATE_CHARGING,        // Charging shot
        STATE_SHOOTING,        // Ball in flight
        STATE_RETURNING        // Ball returning to player
    } phase;
} GameState;

#endif // COMMON_H