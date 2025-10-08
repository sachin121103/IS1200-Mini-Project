#include "../include/common.h"
#include <stdio.h>

// Include the C files directly
#include "utils.c"
#include "physics.c"

/* ===========================
   MAIN TEST PROGRAM
   =========================== */

int main(void) {
    Ball ball;
    Player player = {100, 200, 5};
    
    // Initialize ball at player position
    init_ball(&ball, player.x, player.y);
    
    printf("=== Basketball Physics Test ===\n\n");
    
    printf("Before shooting:\n");
    printf("  Position: (%d, %d)\n", ball.x, ball.y);
    printf("  Velocity: (%d, %d)\n", ball.vx, ball.vy);
    printf("  Active: %s\n", ball.active ? "true" : "false");
    printf("\n");
    
    // Shoot with power 90, angle 45 degrees
    shoot_ball(&ball, 90, 45);
    
    printf("Immediately after shooting:\n");
    printf("  Position: (%d, %d)\n", ball.x, ball.y);
    printf("  Velocity: (%d, %d)\n", ball.vx, ball.vy);
    printf("  Active: %s\n", ball.active ? "true" : "false");
    printf("  Speed: %u px/s\n", get_ball_speed(&ball));
    printf("\n");
    
    printf("Physics simulation (dt=0.033s, ~30 FPS):\n");
    printf("%-8s %-8s %-8s %-8s %-8s\n", "Frame", "X", "Y", "VX", "VY");
    printf("--------------------------------------------------\n");
    
    // Simulate 100 frames max
    for (int frame = 0; frame < 100; frame++) {
        // Print state BEFORE update for frame 0
        if (frame == 0 || frame % 10 == 0) {
            printf("%-8d %-8d %-8d %-8d %-8d\n",
                   frame, ball.x, ball.y, ball.vx, ball.vy);
        }
        
        // Update physics
        update_ball_physics(&ball, 0.033f);
        
        // Check if hit ground
        if (is_ball_on_ground(&ball)) {
            printf("\nBall hit ground at frame %d!\n", frame + 1);
            printf("  Final position: (%d, %d)\n", ball.x, ball.y);
            printf("  Final velocity: (%d, %d)\n", ball.vx, ball.vy);
            printf("  Distance traveled: %d pixels\n", ball.x - player.x);
            break;
        }
        
        // Safety check - ball went off screen
        if (!ball.active) {
            printf("\nBall went off screen at frame %d\n", frame + 1);
            break;
        }
    }
    
    printf("\n=== Test Complete ===\n");
    
    return 0;
}