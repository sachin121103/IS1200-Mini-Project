#include "hardware.h"

// Global variables
static volatile uint32_t* key_ptr = (uint32_t*)KEY_BASE;
static volatile uint32_t* switch_ptr = (uint32_t*)SWITCH_BASE;
static volatile uint32_t* timer_ptr = (uint32_t*)TIMER_BASE;
static uint32_t system_time_ms = 0;

// Timer frequency constant (typically 50MHz for DE1-SoC)
#define TIMER_FREQ_HZ 50000000
#define TIMER_MS_PERIOD (TIMER_FREQ_HZ / 1000)

void init_hardware(void) {
    // Initialize all hardware peripherals
    init_timer();
    // Any other initialization needed for board
}

bool read_hardware_key1(void) {
    // Read KEY1 button (typically bit 1 of KEY register)
    // Buttons are usually active-low
    uint32_t key_value = *key_ptr;
    return (key_value & 0x02) == 0;  // Bit 1 for KEY1
}

bool read_hardware_switch(int switch_num) {
    // Read specific switch
    uint32_t switch_value = *switch_ptr;
    return (switch_value & (1 << switch_num)) != 0;
}

void init_timer(void) {
    // Initialize hardware timer for time tracking
    // Set up timer to run continuously
    
    // Stop timer first
    timer_ptr[1] = 0x08;  // STOP bit
    
    // Set period for 1ms intervals
    uint32_t period = TIMER_MS_PERIOD - 1;
    timer_ptr[2] = period & 0xFFFF;        // Period low
    timer_ptr[3] = (period >> 16) & 0xFFFF; // Period high
    
    // Start timer: START | CONT | ITO (Start, Continuous, Interrupt)
    timer_ptr[1] = 0x07;
    
    system_time_ms = 0;
}

uint32_t get_current_time_ms(void) {
    // Read timer snapshot registers
    // First request a snapshot
    timer_ptr[4];  // Reading snapshot low triggers capture
    
    uint32_t timer_low = timer_ptr[4];
    uint32_t timer_high = timer_ptr[5];
    uint32_t timer_value = (timer_high << 16) | timer_low;
    
    // Convert timer ticks to milliseconds
    // Timer counts down, so calculate elapsed time
    uint32_t elapsed_ticks = TIMER_MS_PERIOD - timer_value;
    uint32_t elapsed_ms = elapsed_ticks / TIMER_MS_PERIOD;
    
    return system_time_ms + elapsed_ms;
}

void delay_ms(uint32_t milliseconds) {
    uint32_t start_time = get_current_time_ms();
    while ((get_current_time_ms() - start_time) < milliseconds) {
        // Busy wait
    }
}

void reset_timer(void) {
    // Stop timer
    timer_ptr[1] = 0x08;
    
    // Reset period
    uint32_t period = TIMER_MS_PERIOD - 1;
    timer_ptr[2] = period & 0xFFFF;
    timer_ptr[3] = (period >> 16) & 0xFFFF;
    
    // Restart timer
    timer_ptr[1] = 0x07;
    
    system_time_ms = 0;
}