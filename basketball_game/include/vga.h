// Corrected header outline:
#define VGA_WIDTH  320
#define VGA_HEIGHT 240
#define VGA_PIXEL_BUFFER0 ((uint16_t*)0x08000000)  
#define VGA_PIXEL_BUFFER1 ((uint16_t*)0x08012C00)
#define VGA_CONTROL_BASE  0xFF203020               

void vga_draw_pixel(int x, int y, uint16_t color);  
uint16_t vga_get_pixel(int x, int y);