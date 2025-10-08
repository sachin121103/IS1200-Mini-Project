#ifndef PHYSICS_H
#define PHYSICS_H

#include "common.h"


void init_ball(Ball* ball, int16_t x, int16_t y);

void shoot_ball(Ball* ball, uint8_t power, int16_t angle);

void update_ball_physics(Ball* ball, float delta_time);

int16_t calculate_shot_angle(uint8_t player_depth);

void reset_ball_to_player(Ball* ball, Player* player);

bool is_ball_on_ground(Ball* ball);

uint16_t get_ball_speed(Ball* ball);

void apply_impulse(Ball* ball, int16_t vx, int16_t vy);

#endif