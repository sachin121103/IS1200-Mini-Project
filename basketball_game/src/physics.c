#include "../include/common.h"

/* ===========================
   EXTERNAL DEPENDENCIES
   =========================== */
// These functions are defined in utils.c
extern int16_t sin_lookup(uint16_t angle);
extern int16_t cos_lookup(uint16_t angle);
extern int16_t clamp(int16_t value, int16_t min, int16_t max);

/* ===========================
   FUNCTION DECLARATIONS
   =========================== */
void init_ball(Ball* ball, int16_t x, int16_t y);
void shoot_ball(Ball* ball, uint8_t power, uint8_t angle);
void update_ball_physics(Ball* ball, float dt);
int16_t calculate_shot_angle(uint8_t depth_position);
void reset_ball_to_player(Ball* ball, int16_t player_x, int16_t player_y);
bool is_ball_on_ground(const Ball* ball);
uint16_t get_ball_speed(const Ball* ball);

/* ===========================
   FUNCTION IMPLEMENTATIONS
   =========================== */

/**
 * Initialize ball at a specific position
 * Sets ball to inactive (not in flight)
 */
void init_ball(Ball* ball, int16_t x, int16_t y) {
    ball->x = x;
    ball->y = y;
    ball->fx = (float)x;
    ball->fy = (float)y;
    ball->vx = 0;
    ball->vy = 0;
    ball->active = false;
}

/**
 * Launch the ball with given power and angle
 * Power: 0-255 (scaled to velocity)
 * Angle: 0-90 degrees (shot trajectory)
 */
void shoot_ball(Ball* ball, uint8_t power, uint8_t angle) {
    // Clamp angle to valid range
    if (angle > 90) {
        angle = 90;
    }
    
    // Calculate velocity components using lookup tables
    // vx = power * cos(angle) / 1000
    // vy = -(power * sin(angle) / 1000)  [negative = upward]
    ball->vx = (power * cos_lookup(angle)) / 1000;
    ball->vy = -(power * sin_lookup(angle)) / 1000;
    
    // Activate the ball
    ball->active = true;
    
    // Initialize fractional accumulators
    ball->fx = (float)ball->x;
    ball->fy = (float)ball->y;
}

/**
 * Update ball physics for one frame
 * dt: Time step in seconds (typically 0.033 for 30 FPS)
 * 
 * Uses projectile motion equations:
 *   x(t) = x0 + vx * dt
 *   y(t) = y0 + vy * dt
 *   vy(t) = vy0 + g * dt
 */
void update_ball_physics(Ball* ball, float dt) {
    if (!ball->active) {
        return;
    }
    
    // Update fractional position (sub-pixel precision)
    ball->fx += ball->vx * dt;
    ball->fy += ball->vy * dt;
    
    // Update integer position (for rendering)
    ball->x = (int16_t)ball->fx;
    ball->y = (int16_t)ball->fy;
    
    // Apply gravity to vertical velocity
    ball->vy += GRAVITY * dt;
    
    // Keep ball within screen bounds (horizontal)
    if (ball->x < BALL_RADIUS) {
        ball->x = BALL_RADIUS;
        ball->fx = (float)BALL_RADIUS;
        ball->vx = -ball->vx / 2;  // Bounce with damping
    } else if (ball->x > SCREEN_WIDTH - BALL_RADIUS) {
        ball->x = SCREEN_WIDTH - BALL_RADIUS;
        ball->fx = (float)(SCREEN_WIDTH - BALL_RADIUS);
        ball->vx = -ball->vx / 2;  // Bounce with damping
    }
}

/**
 * Calculate shot angle based on player's depth position
 * Closer to hoop = lower arc, farther = higher arc
 * 
 * depth_position: 0 (close) to 10 (far)
 * Returns: Angle in degrees (30-60 range)
 */
int16_t calculate_shot_angle(uint8_t depth_position) {
    // Clamp depth to valid range
    if (depth_position > 10) {
        depth_position = 10;
    }
    
    // Map depth (0-10) to angle (30-60 degrees)
    // Close shots use lower arc, far shots use higher arc
    return 30 + (depth_position * 3);
}

/**
 * Reset ball to player's position
 * Used when returning ball after a shot
 */
void reset_ball_to_player(Ball* ball, int16_t player_x, int16_t player_y) {
    ball->x = player_x;
    ball->y = player_y - 20;  // Slightly above player
    ball->fx = (float)ball->x;
    ball->fy = (float)ball->y;
    ball->vx = 0;
    ball->vy = 0;
    ball->active = false;
}

/**
 * Check if ball has hit the ground
 * Returns true if ball is at or below floor level
 */
bool is_ball_on_ground(const Ball* ball) {
    // Ground is at bottom of screen
    return (ball->y >= SCREEN_HEIGHT - BALL_RADIUS);
}

uint16_t get_ball_speed(const Ball* ball) {
    int16_t vx_abs = abs_value(ball->vx);
    int16_t vy_abs = abs_value(ball->vy);
    uint32_t speed_squared = (uint32_t)(vx_abs * vx_abs) + (uint32_t)(vy_abs * vy_abs);
    return int_sqrt(speed_squared);
}