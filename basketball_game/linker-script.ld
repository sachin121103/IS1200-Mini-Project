OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    SDRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 64M
    VGA (rw)    : ORIGIN = 0x08000000, LENGTH = 153600
}

SECTIONS
{
    .text.init : ALIGN(4)
    {
        *(.text.init)
        . = ALIGN(4);
    } > SDRAM

    .text : ALIGN(4)
    {
        *(.text)
        *(.text.*)
        . = ALIGN(4);
    } > SDRAM

    .rodata : ALIGN(4)
    {
        *(.rodata)
        *(.rodata.*)
        *(.srodata)
        *(.srodata.*)
        . = ALIGN(4);
    } > SDRAM

    .data : ALIGN(4)
    {
        __data_start = .;
        *(.data)
        *(.data.*)
        *(.sdata)
        *(.sdata.*)
        . = ALIGN(4);
        __data_end = .;
    } > SDRAM

    __data_load = LOADADDR(.data);

    .bss (NOLOAD) : ALIGN(4)
    {
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        *(.sbss)
        *(.sbss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > SDRAM

    .stack (NOLOAD) : ALIGN(16)
    {
        __stack_bottom = .;
        . = . + 16K;
        __stack_top = .;
    } > SDRAM

    .heap (NOLOAD) : ALIGN(4)
    {
        __heap_start = .;
        . = . + 8K;
        __heap_end = .;
    } > SDRAM

    /DISCARD/ :
    {
        *(.comment)
        *(.note*)
        *(.eh_frame)
        *(.eh_frame_hdr)
    }
}