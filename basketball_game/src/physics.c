#include "../include/physics.h"
#include "../include/utils.h"
#include "../include/common.h"


#define PHYSICS_GRAVITY GRAVITY
#define AIR_RESISTANCE 0.0f
#define BOUNCE_FACTOR 0.0f
#define MIN_VELOCITY_THRESHOLD 1



static void apply_gravity(Ball* ball, float delta_time);
static void apply_air_resistance(Ball* ball, float delta_time);
static int16_t calculate_initial_vx(uint8_t power, int16_t angle);
static int16_t calculate_initial_vy(uint8_t power, int16_t angle);



void init_ball(Ball* ball, int16_t x, int16_t y) {
    ball->x = x;
    ball->y = y;
    ball->vx = 0;
    ball->vy = 0;
    ball->active = false;
}

void shoot_ball(Ball* ball, uint8_t power, int16_t angle) {
    if (power < MIN_SHOT_POWER) {
        power = MIN_SHOT_POWER;
    }
    if (power > MAX_SHOT_POWER) {
        power = MAX_SHOT_POWER;
    }
    
    if (angle < 0) {
        angle = 0;
    }
    if (angle > 90) {
        angle = 90;
    }
    
    ball->vx = calculate_initial_vx(power, angle);
    ball->vy = calculate_initial_vy(power, angle);
    
    /* Mark ball as in flight */
    ball->active = true;
}

void update_ball_physics(Ball* ball, float delta_time) {
    if (!ball->active) {
        return;
    }

    ball->x += (int16_t)(ball->vx * delta_time);
    ball->y += (int16_t)(ball->vy * delta_time);

    apply_gravity(ball, delta_time);
    
    if (AIR_RESISTANCE > 0.0f) {
        apply_air_resistance(ball, delta_time);
    }
    
    if (ball->x < -100 || ball->x > SCREEN_WIDTH + 100) {
        ball->active = false;
    }
    if (ball->y > SCREEN_HEIGHT + 100) {
        ball->active = false;
    }
}

int16_t calculate_shot_angle(uint8_t player_depth) {

    
    /* Clamp depth to valid range */
    if (player_depth > PLAYER_MAX_DEPTH) {
        player_depth = PLAYER_MAX_DEPTH;
    }
    
    /* Base angle for medium distance */
    int16_t base_angle = 50;

    int16_t angle_adjustment = (PLAYER_MAX_DEPTH - player_depth) * 1;
    
    int16_t final_angle = base_angle + angle_adjustment;
    
    if (final_angle < 40) {
        final_angle = 40;
    }
    if (final_angle > 70) {
        final_angle = 70;
    }
    
    return final_angle;
}

void reset_ball_to_player(Ball* ball, Player* player) {
    ball->x = player->x;
    ball->y = player->y - (PLAYER_HEIGHT / 2) - BALL_RADIUS;
    
    ball->vx = 0;
    ball->vy = 0;
    
    /* Mark as inactive */
    ball->active = false;
}

bool is_ball_on_ground(Ball* ball) {
    /* Check if bottom of ball is at or below floor level */
    int16_t ball_bottom = ball->y + BALL_RADIUS;
    return (ball_bottom >= FLOOR_Y);
}

uint16_t get_ball_speed(Ball* ball) {
    /* Calculate magnitude of velocity vector
       speed = sqrt(vx^2 + vy^2)
    */
    int32_t vx_squared = (int32_t)ball->vx * (int32_t)ball->vx;
    int32_t vy_squared = (int32_t)ball->vy * (int32_t)ball->vy;
    uint32_t speed_squared = vx_squared + vy_squared;
    
    return (uint16_t)int_sqrt(speed_squared);
}

void apply_impulse(Ball* ball, int16_t vx, int16_t vy) {
    ball->vx += vx;
    ball->vy += vy;
}

static void apply_gravity(Ball* ball, float delta_time) {

    int16_t gravity_delta = (int16_t)(PHYSICS_GRAVITY * delta_time);
    ball->vy += gravity_delta;
    
    if (ball->vy > 500) {
        ball->vy = 500;
    }
}

static void apply_air_resistance(Ball* ball, float delta_time) {
    /* Apply air resistance (drag force)
       F_drag = -k * v
    */
    
    if (AIR_RESISTANCE == 0.0f) {
        return;
    }
    
    /* Apply resistance proportional to velocity */
    float resistance_factor = 1.0f - (AIR_RESISTANCE * delta_time);
    
    if (resistance_factor < 0.0f) {
        resistance_factor = 0.0f;
    }
    
    ball->vx = (int16_t)(ball->vx * resistance_factor);
    ball->vy = (int16_t)(ball->vy * resistance_factor);
}

static int16_t calculate_initial_vx(uint8_t power, int16_t angle) {
    
    int16_t cos_value = cos_lookup(angle);
    
    int32_t vx = ((int32_t)power * (int32_t)cos_value) / 1000;
    
    return (int16_t)vx;
}

static int16_t calculate_initial_vy(uint8_t power, int16_t angle) {
    int16_t sin_value = sin_lookup(angle);
    
    /* -(power * sin(angle) / 1000) */
    int32_t vy = -((int32_t)power * (int32_t)sin_value) / 1000;
    
    return (int16_t)vy;
}