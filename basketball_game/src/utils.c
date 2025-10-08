#include "../include/common.h"

/* ===========================
   FUNCTION DECLARATIONS
   =========================== */
int16_t sin_lookup(uint16_t angle);
int16_t cos_lookup(uint16_t angle);
int16_t clamp(int16_t value, int16_t min, int16_t max);
int16_t map_range(int16_t value, int16_t in_min, int16_t in_max, 
                  int16_t out_min, int16_t out_max);
void int_to_string(int32_t value, char* buffer, uint8_t buffer_size);
int16_t abs_value(int16_t value);
uint16_t int_sqrt(uint32_t value);

/* ===========================
   LOOKUP TABLES
   =========================== */

// Pre-computed sine values for 0-90 degrees (scaled by 1000)
// sin(angle) ≈ sin_table[angle] / 1000
static const int16_t sin_table[91] = {
    0,    17,   35,   52,   70,   87,   105,  122,  139,  156,  // 0-9
    174,  191,  208,  225,  242,  259,  276,  292,  309,  326,  // 10-19
    342,  358,  375,  391,  407,  423,  438,  454,  469,  485,  // 20-29
    500,  515,  530,  545,  559,  574,  588,  602,  616,  629,  // 30-39
    643,  656,  669,  682,  695,  707,  719,  731,  743,  755,  // 40-49
    766,  777,  788,  799,  809,  819,  829,  839,  848,  857,  // 50-59
    866,  875,  883,  891,  899,  906,  914,  921,  927,  934,  // 60-69
    940,  946,  951,  956,  961,  966,  970,  974,  978,  982,  // 70-79
    985,  988,  990,  993,  995,  996,  998,  999,  999, 1000,  // 80-89
    1000                                                         // 90
};

// Pre-computed cosine values for 0-90 degrees (scaled by 1000)
// cos(angle) ≈ cos_table[angle] / 1000
static const int16_t cos_table[91] = {
    1000, 1000,  999,  999,  998,  996,  995,  993,  990,  988,  // 0-9
    985,  982,  978,  974,  970,  966,  961,  956,  951,  946,  // 10-19
    940,  934,  927,  921,  914,  906,  899,  891,  883,  875,  // 20-29
    866,  857,  848,  839,  829,  819,  809,  799,  788,  777,  // 30-39
    766,  755,  743,  731,  719,  707,  695,  682,  669,  656,  // 40-49
    643,  629,  616,  602,  588,  574,  559,  545,  530,  515,  // 50-59
    500,  485,  469,  454,  438,  423,  407,  391,  375,  358,  // 60-69
    342,  326,  309,  292,  276,  259,  242,  225,  208,  191,  // 70-79
    174,  156,  139,  122,  105,   87,   70,   52,   35,   17,  // 80-89
    0                                                            // 90
};

/* ===========================
   FUNCTION IMPLEMENTATIONS
   =========================== */

/**
 * Get sine of angle (0-90 degrees)
 * Returns value scaled by 1000 (sin = result/1000)
 */
int16_t sin_lookup(uint16_t angle) {
    if (angle > 90) {
        angle = 90;
    }
    return sin_table[angle];
}

/**
 * Get cosine of angle (0-90 degrees)
 * Returns value scaled by 1000 (cos = result/1000)
 */
int16_t cos_lookup(uint16_t angle) {
    if (angle > 90) {
        angle = 90;
    }
    return cos_table[angle];
}

/**
 * Clamp value between min and max
 */
int16_t clamp(int16_t value, int16_t min, int16_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * Map value from one range to another (linear interpolation)
 */
int16_t map_range(int16_t value, int16_t in_min, int16_t in_max, 
                  int16_t out_min, int16_t out_max) {
    // Clamp input to input range
    if (value < in_min) value = in_min;
    if (value > in_max) value = in_max;
    
    // Map to output range
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * Convert integer to string (handles negative numbers)
 */
void int_to_string(int32_t value, char* buffer, uint8_t buffer_size) {
    uint8_t i = 0;
    bool is_negative = false;
    
    // Handle negative numbers
    if (value < 0) {
        is_negative = true;
        value = -value;
    }
    
    // Handle zero case
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }
    
    // Convert digits (reverse order)
    char temp[12]; // Max digits for 32-bit int
    uint8_t temp_i = 0;
    
    while (value > 0 && temp_i < 11) {
        temp[temp_i++] = '0' + (value % 10);
        value /= 10;
    }
    
    // Add negative sign if needed
    if (is_negative && i < buffer_size - 1) {
        buffer[i++] = '-';
    }
    
    // Copy digits in correct order
    while (temp_i > 0 && i < buffer_size - 1) {
        buffer[i++] = temp[--temp_i];
    }
    
    buffer[i] = '\0';
}

/**
 * Get absolute value
 */
int16_t abs_value(int16_t value) {
    return (value < 0) ? -value : value;
}

/**
 * Integer square root using Newton's method
 */
uint16_t int_sqrt(uint32_t value) {
    if (value == 0) return 0;
    if (value == 1) return 1;
    
    uint32_t x = value;
    uint32_t y = (x + 1) / 2;
    
    // Newton's method: iterate until convergence
    while (y < x) {
        x = y;
        y = (x + value / x) / 2;
    }
    
    return (uint16_t)x;
}