#include "../include/utils.h"


static const int16_t sin_table_90[] = {
    0, 17, 35, 52, 70, 87, 105, 122, 139, 156,  // 0-9
    174, 191, 208, 225, 242, 259, 276, 292, 309, 326,  // 10-19
    342, 358, 375, 391, 407, 423, 438, 454, 469, 485,  // 20-29
    500, 515, 530, 545, 559, 574, 588, 602, 616, 629,  // 30-39
    643, 656, 669, 682, 695, 707, 719, 731, 743, 755,  // 40-49
    766, 777, 788, 799, 809, 819, 829, 839, 848, 857,  // 50-59
    866, 875, 883, 891, 899, 906, 914, 921, 927, 934,  // 60-69
    940, 946, 951, 956, 961, 966, 970, 974, 978, 982,  // 70-79
    985, 988, 990, 993, 995, 996, 998, 999, 999, 1000, 1000  // 80-90
};

int16_t sin_lookup(int16_t angle) {
    if (angle < 0) {
        angle = 0;
    }
    if (angle > 90) {
        angle = 90;
    }
    
    return sin_table_90[angle];
}

int16_t cos_lookup(int16_t angle) {
    if (angle < 0) {
        angle = 0;
    }
    if (angle > 90) {
        angle = 90;
    }
    
    return sin_lookup(90 - angle);
}

int32_t fixed_multiply(int32_t a, int32_t b, uint8_t shift) {
    int32_t result = (int32_t)a * (int32_t)b;
    return (int32_t)(result >> shift);
}

int32_t fixed_divide(int32_t a, int32_t b, uint8_t shift) {
    if (b == 0) {
        return 0;
    }
    int32_t result = ((int32_t)a << shift) / b;
    return (int32_t)result;
}

uint32_t int_sqrt(uint32_t n) {
    if (n == 0) {
        return 0;
    }
    
    uint32_t x = n;
    uint32_t y = (x + 1) / 2;
    
    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }
    
    return x;
}

int16_t abs_value(int16_t x) {
    return (x < 0) ? -x : x;
}

int16_t clamp(int16_t value, int16_t min, int16_t max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

int16_t map_range(int16_t value, int16_t in_min, int16_t in_max, 
                  int16_t out_min, int16_t out_max) {

    if (in_max == in_min) {
        return out_min;
    }
    
    int32_t in_range = in_max - in_min;
    int32_t out_range = out_max - out_min;
    int32_t scaled_value = (value - in_min) * out_range;
    
    return out_min + (int16_t)(scaled_value / in_range);
}

void int_to_string(int num, char* buffer) {

    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    int i = 0;
    int is_negative = 0;
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    
    if (is_negative) {
        buffer[i++] = '-';
    }
    
    /* Null terminate */
    buffer[i] = '\0';
    
    reverse_string(buffer, i);
}

int string_length(const char* str) {
    int length = 0;
    
    while (str[length] != '\0') {
        length++;
    }
    
    return length;
}

void reverse_string(char* str, int length) {
    int start = 0;
    int end = length - 1;
    
    while (start < end) {
        /* Swap characters */
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        
        start++;
        end--;
    }
}

void busy_wait(uint32_t cycles) {
    for (volatile uint32_t i = 0; i < cycles; i++) {
        /* Do nothing, just wait */
    }
}

int16_t min_int16(int16_t a, int16_t b) {
    return (a < b) ? a : b;
}

int16_t max_int16(int16_t a, int16_t b) {
    return (a > b) ? a : b;
}