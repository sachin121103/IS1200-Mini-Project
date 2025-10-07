# =========================================================================
# RISC-V Startup Code for DE10-Lite (SDRAM-based System)
# Basketball Game Project
#
# This code runs BEFORE main() and sets up the processor environment:
# - Sets up stack pointer
# - Clears BSS section (uninitialized variables)
# - Sets up trap handler
# - Calls main()
# =========================================================================

    .section .text.init
    .global _start
    .type _start, @function

_start:
    # Disable interrupts during initialization
    csrw mie, zero

    # Set up stack pointer
    # Stack grows downward from __stack_top (defined in linker script)
    la sp, __stack_top

    # Clear BSS section (uninitialized global variables)
    # BSS must be zeroed according to C standard
    la t0, __bss_start
    la t1, __bss_end
    beq t0, t1, bss_done

clear_bss:
    sw zero, 0(t0)
    addi t0, t0, 4
    blt t0, t1, clear_bss

bss_done:
    # Note: For DE10-Lite (SDRAM-based system), we DON'T need to copy
    # .data section from ROM to RAM because everything is already in SDRAM

    # Set up trap vector (for interrupts and exceptions)
    la t0, trap_handler
    csrw mtvec, t0

    # Call main function
    call main

    # If main returns, halt the processor
halt:
    j halt

    .size _start, . - _start

# =========================================================================
# Trap Handler (Interrupts and Exceptions)
#
# This is called when:
# - Hardware interrupt occurs (timer, button press, etc.)
# - Exception occurs (illegal instruction, misaligned access, etc.)
# =========================================================================

    .align 4
    .global trap_handler
    .type trap_handler, @function

trap_handler:
    # Save all registers to stack
    addi sp, sp, -128

    # Save caller-saved registers (x1, x5-x7, x10-x17, x28-x31)
    sw x1,   0(sp)      # ra (return address)
    sw x5,  16(sp)      # t0
    sw x6,  20(sp)      # t1
    sw x7,  24(sp)      # t2
    sw x8,  28(sp)      # s0/fp
    sw x9,  32(sp)      # s1
    sw x10, 36(sp)      # a0
    sw x11, 40(sp)      # a1
    sw x12, 44(sp)      # a2
    sw x13, 48(sp)      # a3
    sw x14, 52(sp)      # a4
    sw x15, 56(sp)      # a5
    sw x16, 60(sp)      # a6
    sw x17, 64(sp)      # a7
    sw x18, 68(sp)      # s2
    sw x19, 72(sp)      # s3
    sw x20, 76(sp)      # s4
    sw x21, 80(sp)      # s5
    sw x22, 84(sp)      # s6
    sw x23, 88(sp)      # s7
    sw x24, 92(sp)      # s8
    sw x25, 96(sp)      # s9
    sw x26, 100(sp)     # s10
    sw x27, 104(sp)     # s11
    sw x28, 108(sp)     # t3
    sw x29, 112(sp)     # t4
    sw x30, 116(sp)     # t5
    sw x31, 120(sp)     # t6

    # Handle the trap here
    # TODO: Add interrupt/exception handling code if needed
    # For now, just return

    # Restore all registers from stack
    lw x1,   0(sp)      # ra
    lw x5,  16(sp)      # t0
    lw x6,  20(sp)      # t1
    lw x7,  24(sp)      # t2
    lw x8,  28(sp)      # s0/fp
    lw x9,  32(sp)      # s1
    lw x10, 36(sp)      # a0
    lw x11, 40(sp)      # a1
    lw x12, 44(sp)      # a2
    lw x13, 48(sp)      # a3
    lw x14, 52(sp)      # a4
    lw x15, 56(sp)      # a5
    lw x16, 60(sp)      # a6
    lw x17, 64(sp)      # a7
    lw x18, 68(sp)      # s2
    lw x19, 72(sp)      # s3
    lw x20, 76(sp)      # s4
    lw x21, 80(sp)      # s5
    lw x22, 84(sp)      # s6
    lw x23, 88(sp)      # s7
    lw x24, 92(sp)      # s8
    lw x25, 96(sp)      # s9
    lw x26, 100(sp)     # s10
    lw x27, 104(sp)     # s11
    lw x28, 108(sp)     # t3
    lw x29, 112(sp)     # t4
    lw x30, 116(sp)     # t5
    lw x31, 120(sp)     # t6

    addi sp, sp, 128

    # Return from trap
    mret

    .size trap_handler, . - trap_handler

