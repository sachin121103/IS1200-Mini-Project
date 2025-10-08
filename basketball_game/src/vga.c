#include "vga.h"

// IMPORTANT: Verify this address with your board documentation!
#define VGA_PIXEL_BUFFER_BASE 0xC8000000

static volatile uint16_t* pixel_buffer = 
    (uint16_t*)VGA_PIXEL_BUFFER_BASE;

void vga_init(void) {
    // Initialize VGA controller if needed
    // Some boards auto-initialize
    vga_clear(COLOR_BLACK);
}

void vga_clear(uint16_t color) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        pixel_buffer[i] = color;
    }
}

void vga_draw_pixel(int x, int y, uint16_t color) {
    // Bounds check
    if (x < 0 || x >= SCREEN_WIDTH || 
        y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    
    int offset = y * SCREEN_WIDTH + x;
    pixel_buffer[offset] = color;
}

uint16_t vga_get_pixel(int x, int y) {
    if (x < 0 || x >= SCREEN_WIDTH || 
        y < 0 || y >= SCREEN_HEIGHT) {
        return 0;
    }
    
    int offset = y * SCREEN_WIDTH + x;
    return pixel_buffer[offset];
}