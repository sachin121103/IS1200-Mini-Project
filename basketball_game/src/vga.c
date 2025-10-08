#include "../include/vga.h"
/ Pointer to pixel buffer
static volatile uint16_t *pixel_buffer = (uint16_t *)VGA_PIXEL_BUFFER_BASE;

// Pointer to character buffer (if needed)
static volatile uint8_t *char_buffer = (uint8_t *)VGA_CHAR_BUFFER_BASE;

// Pointer to VGA control registers
static volatile uint32_t *vga_control = (uint32_t *)VGA_CONTROL_BASE;

/**
 * Initialize the VGA controller
 */
void vga_init(void) {
    // Clear the pixel buffer
    vga_clear(0x0000);
    
    // Additional initialization if needed
    // For example, setting up double buffering or control registers
    // This depends on your specific hardware
}

/**
 * Clear the screen with a specific color
 */
void vga_clear(uint16_t color) {
    int i;
    int total_pixels = VGA_WIDTH * VGA_HEIGHT;
    
    for (i = 0; i < total_pixels; i++) {
        pixel_buffer[i] = color;
    }
}

/**
 * Draw a pixel at the specified coordinates
 */
void vga_draw_pixel(int x, int y, uint16_t color) {
    // Bounds checking
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return;
    }
    
    // Calculate offset and write pixel
    pixel_buffer[y * VGA_WIDTH + x] = color;
}

/**
 * Get the color of a pixel at the specified coordinates
 */
uint16_t vga_get_pixel(int x, int y) {
    // Bounds checking
    if (x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return 0x0000;
    }
    
    // Read and return pixel color
    return pixel_buffer[y * VGA_WIDTH + x];
}

/**
 * Swap front and back buffers (if double-buffering supported)
 */
void vga_swap_buffers(void) {
    // This implementation depends on your hardware
    // Example for systems with a buffer swap register:
    // Write 1 to the buffer register to swap
    if (vga_control != NULL) {
        *vga_control = 1;
        
        // Wait for swap to complete
        while ((*vga_control & 0x01) != 0) {
            // Busy wait
        }
    }
}

/**
 * Wait for vertical sync signal
 */
void vga_wait_vsync(void) {
    // This implementation depends on your hardware
    // Example for systems with a status register:
    // Wait for vsync bit (bit 3) to be set
    if (vga_control != NULL) {
        // Wait for vsync to start
        while ((*vga_control & 0x08) == 0) {
            // Busy wait
        }
        
        // Wait for vsync to end
        while ((*vga_control & 0x08) != 0) {
            // Busy wait
        }
    }
}

/**
 * Convert RGB888 to RGB565 format
 */
uint16_t rgb_to_rgb565(uint8_t r, uint8_t g, uint8_t b) {
    // RGB565 format: 5 bits red, 6 bits green, 5 bits blue
    uint16_t r5 = (r >> 3) & 0x1F;  // Take top 5 bits of red
    uint16_t g6 = (g >> 2) & 0x3F;  // Take top 6 bits of green
    uint16_t b5 = (b >> 3) & 0x1F;  // Take top 5 bits of blue
    
    return (r5 << 11) | (g6 << 5) | b5;
}