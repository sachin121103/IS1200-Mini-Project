<<<<<<< HEAD
#include "vga.h"
#include "common.h"

int main() {
    init_vga();
    
    // Draw color bars
    vga_draw_rect(0, 0, 80, 240, COLOR_RED);
    vga_draw_rect(80, 0, 80, 240, COLOR_GREEN);
    vga_draw_rect(160, 0, 80, 240, COLOR_BLUE);
    vga_draw_rect(240, 0, 80, 240, COLOR_WHITE);
    
    // Infinite loop - keep display active
    while(1);
=======
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
>>>>>>> 1e3aaa6a6546cea74414e956fc2eaaf9d9b6f432
    
    // Test 2: Draw white cross in center
    for (int i = 0; i < 50; i++) {
        draw_pixel(SCREEN_WIDTH/2 + i, SCREEN_HEIGHT/2, 0xFFFF);
        draw_pixel(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + i, 0xFFFF);
    }
    
    while(1);  // Hang to see result
    return 0;
}