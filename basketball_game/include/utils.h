#ifndef UTILS_H
#define UTILS_H

#include "common.h"

int16_t sin_lookup(int16_t angle);
int16_t cos_lookup(int16_t angle);

int32_t fixed_multiply(int32_t a, int32_t b, uint8_t shift);
int32_t fixed_divide(int32_t a, int32_t b, uint8_t shift);

int16_t abs_value(int16_t x);

uint32_t int_sqrt(uint32_t n);

int16_t clamp(int16_t value, int16_t min, int16_t max);

int16_t map_range(int16_t value, int16_t in_min, int16_t in_max, 
                  int16_t out_min, int16_t out_max);


void int_to_string(int num, char* buffer);

int string_length(const char* str);

void reverse_string(char* str, int length);

void busy_wait(uint32_t cycles);

int16_t min_int16(int16_t a, int16_t b);
int16_t max_int16(int16_t a, int16_t b);

#endif 