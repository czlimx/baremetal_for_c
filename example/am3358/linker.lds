MEMORY
{   
    normal(xrw)   : ORIGIN = 0xC2000000, LENGTH = 480M
    shareable(rw) : ORIGIN = 0xC1000000, LENGTH = 16M
    page_table(x) : ORIGIN = 0xC0000000, LENGTH = 16M
}
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
    .text : {
        . = ALIGN(256);
        *(.text.arch.vectors)
        *(.text.arch.startup)
        *(.text.arch.*)
        *(.text.device.*)
        *(.text.driver.*)
        *(.text.tryrtos.*)
        *(.text*)
    } > normal

    .rodata : {
        . = ALIGN(256);
        *(.rodata*)
    } > normal

    .data : {
        . = ALIGN(256);
        *(.data*)
    } > normal

    .bss (NOLOAD) : {
        . = ALIGN(256);
        _bss_start_ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(256);
        _bss_end_ = .;
    } > normal

    .stack (NOLOAD) : {
        . = ALIGN(256);
        . = . + 0x4000;
        _stack_end = .;
    } > normal

    .share : {
        . = ALIGN(256);
        *(.share*)
    } > shareable
}
