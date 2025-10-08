#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>
#include <stdbool.h>

// Hardware register addresses (adjust for DTEK-V)
#define KEY_BASE 0xFF200050
#define SWITCH_BASE 0xFF200040
#define TIMER_BASE 0xFF202000

// Timer register offsets
#define TIMER_STATUS 0x0
#define TIMER_CONTROL 0x4
#define TIMER_PERIODL 0x8
#define TIMER_PERIODH 0xC
#define TIMER_SNAPL 0x10
#define TIMER_SNAPH 0x14

// Function declarations

/**
 * Initialize hardware components (keys, switches, timer)
 */
void init_hardware(void);

/**
 * Read the state of hardware KEY1
 * @return true if KEY1 is pressed, false otherwise
 */
bool read_hardware_key1(void);

/**
 * Read the state of a specific switch
 * @param switch_num The switch number to read (0-9 typically)
 * @return true if switch is in ON position, false otherwise
 */
bool read_hardware_switch(int switch_num);

/**
 * Get current time in milliseconds since timer initialization
 * @return Current time in milliseconds
 */
uint32_t get_current_time_ms(void);

/**
 * Delay execution for specified milliseconds
 * @param milliseconds Time to delay in milliseconds
 */
void delay_ms(uint32_t milliseconds);

/**
 * Initialize the hardware timer
 */
void init_timer(void);

/**
 * Reset the timer counter to zero
 */
void reset_timer(void);

#endif // HARDWARE_H