MEMORY
{   
    SRAM(xrw)  : ORIGIN = 0x402F0400, LENGTH = 127K
    DRAM(xrw)  : ORIGIN = 0x80000000, LENGTH = 512M
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
        *(.text.*)
        *(.text*)
        *(.glue*)
        *(.vfp*)
        *(.v4*)
        *(*.iplt*)
    } > DRAM

    .rodata : {
        . = ALIGN(256);
        *(.rodata*)
    } > DRAM

    .data : {
        . = ALIGN(256);
        *(.data*)
        *(.igot*)
    } > DRAM

    .bss (NOLOAD) : {
        . = ALIGN(256);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(256);
        __bss_end__ = .;
    } > DRAM

    .stack (NOLOAD) : {
        . = ALIGN(256);
        __stack_start__ = .;
        . = . + 0x1000;
        __stack_abt_end__ = .;
        . = . + 0x100000;
        __stack_irq_end__ = .;
        . = . + 0x100000;
        __stack_svc_end__ = .;
        . = . + 0x100000;
        __stack_sys_end__ = .;
        . = . + 0xA00000;
        __stack_end__ = .;
    } > DRAM
}
