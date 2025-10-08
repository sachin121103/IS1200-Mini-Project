// test_vga.c - Run this first on the board
#include <stdint.h>

#define VGA_BASE 0xC8000000  // ADJUST THIS!
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

volatile uint16_t* pixel_buffer = (uint16_t*)VGA_BASE;

void draw_pixel(int x, int y, uint16_t color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        pixel_buffer[y * SCREEN_WIDTH + x] = color;
    }
}

int main(void) {
    // Test 1: Fill screen with red
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            draw_pixel(x, y, 0xF800);  // Red in RGB565
        }
    }
    
    // Test 2: Draw white cross in center
    for (int i = 0; i < 50; i++) {
        draw_pixel(SCREEN_WIDTH/2 + i, SCREEN_HEIGHT/2, 0xFFFF);
        draw_pixel(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + i, 0xFFFF);
    }
    
    while(1);  // Hang to see result
    return 0;
}