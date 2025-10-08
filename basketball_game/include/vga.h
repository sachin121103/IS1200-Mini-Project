#ifndef VGA_H
#define VGA_H

#include "common.h"
#include <stdint.h>

// VGA hardware addresses (adjust for your board!)
#define VGA_PIXEL_BUFFER_BASE   0xC8000000
#define VGA_CHAR_BUFFER_BASE    0xC9000000
#define VGA_CONTROL_BASE        0xFF203020

// VGA resolution constants
#define VGA_WIDTH               320
#define VGA_HEIGHT              240

// Function declarations

/**
 * Initialize the VGA controller
 */
void vga_init(void);

/**
 * Clear the screen with a specific color
 * @param color: RGB565 color value
 */
void vga_clear(uint16_t color);

/**
 * Draw a pixel at the specified coordinates
 * @param x: X coordinate (0 to VGA_WIDTH-1)
 * @param y: Y coordinate (0 to VGA_HEIGHT-1)
 * @param color: RGB565 color value
 */
void vga_draw_pixel(int x, int y, uint16_t color);

/**
 * Get the color of a pixel at the specified coordinates
 * @param x: X coordinate
 * @param y: Y coordinate
 * @return RGB565 color value
 */
uint16_t vga_get_pixel(int x, int y);

/**
 * Swap front and back buffers (if double-buffering supported)
 */
void vga_swap_buffers(void);

/**
 * Wait for vertical sync signal
 */
void vga_wait_vsync(void);

/**
 * Convert RGB888 to RGB565 format
 * @param r: Red component (0-255)
 * @param g: Green component (0-255)
 * @param b: Blue component (0-255)
 * @return RGB565 color value
 */
uint16_t rgb_to_rgb565(uint8_t r, uint8_t g, uint8_t b);

#endif // VGA_H