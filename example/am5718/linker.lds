MEMORY
{   
    dram(xrw)  : ORIGIN = 0x40300000, LENGTH = 512K
    sram(xrw)  : ORIGIN = 0x80000000, LENGTH = 1024M
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
    } > dram

    .rodata : {
        . = ALIGN(256);
        *(.rodata*)
    } > dram

    .data : {
        . = ALIGN(256);
        *(.data*)
    } > dram

    .bss (NOLOAD) : {
        . = ALIGN(256);
        _bss_start_ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(256);
        _bss_end_ = .;
    } > dram

    .stack (NOLOAD) : {
        . = ALIGN(256);
        . = . + 0x4000;
        _stack_end = .;
    } > dram
}
