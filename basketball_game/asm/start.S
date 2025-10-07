# Basketball Game - RISC-V Startup Code
# This runs before main() and initializes the system

    .section .text.init
    .global _start
    .type _start, @function

_start:
    # Disable interrupts during initialization
    csrw mie, zero

    # Set up stack pointer
    la sp, __stack_top

    # Clear BSS section (uninitialized data)
    la t0, __bss_start
    la t1, __bss_end
    beq t0, t1, bss_done
clear_bss:
    sw zero, 0(t0)
    addi t0, t0, 4
    blt t0, t1, clear_bss

bss_done:
    # Copy initialized data from ROM to RAM
    la t0, __data_start      # Destination (RAM)
    la t1, __data_end        # End of data section
    la t2, __data_load       # Source (ROM)
    beq t0, t1, data_done
copy_data:
    lw t3, 0(t2)
    sw t3, 0(t0)
    addi t0, t0, 4
    addi t2, t2, 4
    blt t0, t1, copy_data

data_done:
    # Set up trap vector (optional - for interrupts/exceptions)
    la t0, trap_handler
    csrw mtvec, t0

    # Call main function
    call main

    # If main returns, halt
halt:
    j halt

    .size _start, . - _start

# Trap handler (interrupts and exceptions)
    .align 4
    .global trap_handler
trap_handler:
    # Save all registers
    addi sp, sp, -128
    sw x1,  0(sp)
    sw x2,  4(sp)
    sw x3,  8(sp)
    sw x4,  12(sp)
    sw x5,  16(sp)
    sw x6,  20(sp)
    sw x7,  24(sp)
    sw x8,  28(sp)
    sw x9,  32(sp)
    sw x10, 36(sp)
    sw x11, 40(sp)
    sw x12, 44(sp)
    sw x13, 48(sp)
    sw x14, 52(sp)
    sw x15, 56(sp)
    sw x16, 60(sp)
    sw x17, 64(sp)
    sw x18, 68(sp)
    sw x19, 72(sp)
    sw x20, 76(sp)
    sw x21, 80(sp)
    sw x22, 84(sp)
    sw x23, 88(sp)
    sw x24, 92(sp)
    sw x25, 96(sp)
    sw x26, 100(sp)
    sw x27, 104(sp)
    sw x28, 108(sp)
    sw x29, 112(sp)
    sw x30, 116(sp)
    sw x31, 120(sp)

    # Handle trap (call C handler if needed)
    # For now, just return

    # Restore all registers
    lw x1,  0(sp)
    lw x2,  4(sp)
    lw x3,  8(sp)
    lw x4,  12(sp)
    lw x5,  16(sp)
    lw x6,  20(sp)
    lw x7,  24(sp)
    lw x8,  28(sp)
    lw x9,  32(sp)
    lw x10, 36(sp)
    lw x11, 40(sp)
    lw x12, 44(sp)
    lw x13, 48(sp)
    lw x14, 52(sp)
    lw x15, 56(sp)
    lw x16, 60(sp)
    lw x17, 64(sp)
    lw x18, 68(sp)
    lw x19, 72(sp)
    lw x20, 76(sp)
    lw x21, 80(sp)
    lw x22, 84(sp)
    lw x23, 88(sp)
    lw x24, 92(sp)
    lw x25, 96(sp)
    lw x26, 100(sp)
    lw x27, 104(sp)
    lw x28, 108(sp)
    lw x29, 112(sp)
    lw x30, 116(sp)
    lw x31, 120(sp)
    addi sp, sp, 128

    # Return from trap
    mret

    .size trap_handler, . - trap_handler