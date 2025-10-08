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
    
    return 0;
}