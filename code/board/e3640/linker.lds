MEMORY
{
    normal(xrw)   : ORIGIN = 0x00404000, LENGTH = 3M
    tcm(xrw)      : ORIGIN = 0x00000100, LENGTH = 64K
}
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
    .vectors : {
        . = ALIGN(256);
        _vectors_start_ = .;
        KEEP(*(.text.arch.vectors))
        . = ALIGN(256);
        _vectors_end_ = .;
    } > normal

    .text : {
        . = ALIGN(256);
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
    } > tcm
}
